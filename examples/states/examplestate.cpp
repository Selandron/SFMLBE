#include "../../release/sfmlbe.hpp"
#include "../../release/tinyxml2.hpp"

/*
	EXAMPLE : HOW TO USE GAME STATES

	To use a game state you need to create your own states that inherit the abstract class sfmlbe::GameState.
	Once you have done that, you need to use the loop from the GameManager that mimic the window loop (see the main function in this file).

	CAREFUL !
	The game manager create (or load if it exist) a file in the same folder than the exe file that contain the caracteristics of the Game
	(i.e. size of window, fullscreen, AA, etc...).
	If the game fail on launch, delete the .ini file and retry.

	USE :
	This example show how to create and use some states.
	In this case, when you press Space you push the second state on top of the first one, or to pop the second one to resume the first one.
	When you press Enter you change the state, you don't push it.
	Because each state have only one instance, even if you can stack the same pointer, if you cleanup one you cleanup all.
	Be careful to prepare you final states machine (to avoid errors or strange behavior like this example).

	IN A GOOD STATES SYSTEM, A STATE CAN ONLY BE ONCE IN THE STACK, AND YOU CANNOT POP THE LAST ONE
	Here this errors are not handled because there can be some cases where it is useful, but avoid them if you can. 

	Map :		Initial
		   	  =>[STATE 1]   --- Enter ---   =>[STATE 2]   --- Enter ---   =>[STATE 1]
				   |							 |							   |
				   |							 |							   |
				 Space						   Space						 Space
				   |							 |							   |
				   |							 |							   |
				   |						   ERROR						   |
				   |														   |
			  =>[STATE 2]   --- Enter ---   =>[STATE 1]	  --- Enter ---   =>[STATE 2]
			    [STATE 1]					  [STATE 1]						[STATE 1]

	How to compile :
	Go in the example folder and use :
	g++ .\states\examplestate.cpp ..\release\sfmlbe.cpp ..\release\tinyxml2.cpp -W -Wall -ansi -std=c++11 -I"SFMLPATH"\include -L"SFMLPATH"\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -o exe1
	Don't forget to add .dll on Windows !

 */

/* DEFINITION OF DIFFERENT STATES STATES */

/* Define a new GameState that does nothing, only print his name */
class FirstGameState : public sfmlbe::GameState
{
	public:
		void Init(sfmlbe::GameManager* game);
		void Cleanup();

		void Pause();
		void Resume();

		void HandleEvents(sfmlbe::GameManager * game);
		void Update(sfmlbe::GameManager * game);
		void Draw(sfmlbe::GameManager * game);

		static FirstGameState * Instance() {return &m_state;}

	protected:
		FirstGameState() { }

	private:
		static FirstGameState m_state;
};

/* Define a new GameState that does nothing, only print his name */
class SecondGameState : public sfmlbe::GameState
{
	public:
		void Init(sfmlbe::GameManager* game);
		void Cleanup();

		void Pause();
		void Resume();

		void HandleEvents(sfmlbe::GameManager * game);
		void Update(sfmlbe::GameManager * game);
		void Draw(sfmlbe::GameManager * game);

		static SecondGameState * Instance() {return &m_state;}

	protected:
		SecondGameState() { }

	private:
		static SecondGameState m_state;
};

/* Declaration of member functions */
FirstGameState FirstGameState::m_state;
void FirstGameState::Init(sfmlbe::GameManager* game) {game->GetWindow()->setKeyRepeatEnabled(false); std::cout << "First Game State init" << std::endl; }
void FirstGameState::Cleanup() { }
void FirstGameState::Pause() { std::cout << "First Game State paused" << std::endl; }
void FirstGameState::Resume() { std::cout << "First Game State resume" << std::endl; }
void FirstGameState::HandleEvents(sfmlbe::GameManager * game)
{
	sf::RenderWindow * window = game->GetWindow();

	sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            game->Quit();
        if (event.type == sf::Event::KeyPressed)
        {
	        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	        	game->ChangeState(SecondGameState::Instance());
	        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        		game->PushState(SecondGameState::Instance());
        }
    }
}
void FirstGameState::Update(sfmlbe::GameManager * game)
{
	sf::RenderWindow * window = game->GetWindow();
	window->clear();
}
void FirstGameState::Draw(sfmlbe::GameManager * game)
{
	sf::RenderWindow * window = game->GetWindow();
	std::cout << "First Game State active" << std::endl;
	window->display();
}


/* Declaration of member functions */
SecondGameState SecondGameState::m_state;
void SecondGameState::Init(sfmlbe::GameManager* game) { std::cout << "Second Game State init" << std::endl; }
void SecondGameState::Cleanup() { }
void SecondGameState::Pause() { std::cout << "Second Game State paused" << std::endl; }
void SecondGameState::Resume() { std::cout << "Second Game State resume" << std::endl; }
void SecondGameState::HandleEvents(sfmlbe::GameManager * game)
{
	sf::RenderWindow * window = game->GetWindow();

	sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            game->Quit();
        if (event.type == sf::Event::KeyPressed)
        {
	        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	        	game->ChangeState(FirstGameState::Instance());
	        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	        	game->PopState();
	    }
    }
}
void SecondGameState::Update(sfmlbe::GameManager * game)
{
	sf::RenderWindow * window = game->GetWindow();
	window->clear();
}
void SecondGameState::Draw(sfmlbe::GameManager * game)
{
	sf::RenderWindow * window = game->GetWindow();
	std::cout << "Second Game State active" << std::endl;
	window->display();
}

int main()
{
	//Create the Game Manager
	sfmlbe::GameManager gameManager;
	//Init with title
	std::string title = "TITLE";
	gameManager.Init(title);

	//Set the first state (without it will not work)
	gameManager.ChangeState(FirstGameState::Instance());

	while (gameManager.Running())
    {
        gameManager.HandleEvents();
        gameManager.Update();
        gameManager.Draw();
    }

    gameManager.Cleanup();

	return 0;
}
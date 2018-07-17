#include "../../release/sfmlbe.hpp"
#include "../../release/tinyxml2.hpp"

/*
	EXAMPLE : HOW TO USE .ini FILE

	The ini file is generated on the first launch of the program next to the binary if it doesn't exist, but you have to use the Game Manager system.
	It is used by the program to store and load options to pass to the window render.
	The file can easily be "corrupted" and the program won't start in that case. To make sure it will work juste delete it and relauch the binary.
	The ini file have to be like that (in this order) :

	fullscreen = false
	width = 640
	height = 480
	dpp = 32
	antialiasing = 0
	frameratemax = 60
	verticalsync = false
	lang = 0

	Boolean field should be false or true only, not 0 or 1. The rest of field are positive or null integers. For width/height/dpp, the triplet should be in the list of sf::VideoMode fullscreen compatible.
	Explainations :
	fullscreen [true|false] : launch the window in fullscreen mode or not
	width [integer] : width of the window
	height [integer] : height of the window
	dpp [integer] : Bits per pixel of the window
	antialiasing [integer] : level of antialiasing
	frameratemax [integer] : max framerate of the window
	verticalsync [true|false] : enable or not the vertical sync (maxframerate should equal 0 if verticalsync is true)
	lang [integer] : describe the lang used (should be in the sfmlbe::LANG enum)

	You can change the caracteristics of the window gy getting them using GetParameters, modify the fields you want and reload it using SetParameters.
	This example show how to dot it. On the first launch the window is small, if you press Enter it will go into fullscreen mode. 
	On the next load it will stay fullscreen, because SetParameters change the .ini and reload the window. Just this function won't reload langage files.

    How to compile :
    Go in the example folder and use :
    g++ .\states\exampleini.cpp ..\release\sfmlbe.cpp ..\release\tinyxml2.cpp -W -Wall -ansi -std=c++11 -I"SFMLPATH"\include -L"SFMLPATH"\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -o exe
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

/* Declaration of member functions */
FirstGameState FirstGameState::m_state;
void FirstGameState::Init(sfmlbe::GameManager* game) { std::cout << "First Game State init" << std::endl; }
void FirstGameState::Cleanup() { }
void FirstGameState::Pause() { }
void FirstGameState::Resume() { }
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
            {
            	sfmlbe::GameParameters params = game->GetParameters();
            	params.fullscreen = true;
            	game->SetParameters(params);
            }
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
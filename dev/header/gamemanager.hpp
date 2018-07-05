#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

/*!
    \file gamemanager.hpp
    \brief Describe a Game Manager class.
    \author Etienne Andrieu
    \version 1.0
 */

#include "common.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

namespace sfmlbe
{

class GameState;

/*!
	\struct GameParameters
	Represent a list of all the caracteristics of the game (and the window).
 */
struct GameParameters
{
    sf::VideoMode windowCaracts;
    bool fullscreen;
    int antialiasingLevel;
    int maxFramerate;
    bool verticalSync;
    LANG lang;
};


/*!
	Class that can handle a game state system.
	Replace the "clear draw display" loop by another loop using a state.
 */
class GameManager
{
	public:

		//! Init the Game Manager.
        /*!
            Init the sf::RenderWindow. Try to use a file next to the exe 'config.ini'.
            If the config file doesn't exist the program create it, but if it's corrupt the programm will not launch.
			\param title Title of the window.
            \sa Cleanup()
        */
		void Init(std::string & title);

		//! Clean the Game Manager.
        /*!
            Pop all states and delete the sf::RenderWindow.
            \sa Init()
        */
		void Cleanup();

		//! Change the current state.
        /*!
            Deletes the last state and replaces it.
            \param state Reference on the state that will be used.
            \sa PushState(GameState * state) and PopState()
        */
		void ChangeState(GameState * state);

		//! Push the current state.
        /*!
            Pauses the current state, pushes the state as parameter on top of the stack and sets as active.
            \param state Reference on the state that will be used.
            \sa ChangeState(GameState * state) and PopState()
        */
		void PushState(GameState * state);

		//! Pop the current state.
        /*!
            Delete the current state from the stack and resume the last one.
            \sa ChangeState(GameState * state) and PushState(GameState * state)
        */
		void PopState();

		//! Call the HandeEvents function on the current state.
        /*!
            \sa Update() and Draw()
        */
		void HandleEvents();

		//! Call the Update function on the current state.
        /*!
            \sa HandleEvents() and Draw()
        */
		void Update();

		//! Call the Draw function on the current state.
        /*!
            \sa HandleEvents() and Update()
        */
		void Draw();

		//! Know if the window is running.
        /*!
        	\return True if the window is running.
            \sa Quit()
        */
		bool Running() { return m_running; }

		//! Stop the infinite loop.
        /*! 
            \sa Running()
        */
		void Quit();

		//! Get the reference on the sf::RenderWindow
        /*!
        	\return Reference on the sf::RenderWindow.
        */
		sf::RenderWindow * GetWindow() { return m_window; }

		//! Get the size of the window.
        /*!
        	\return Size of the window (x, y).
        */
		sf::Vector2u GetSize();

		//! Get the caracteristics of the window and the system.
        /*!
        	\return Parameters of the game.
        */
		GameParameters GetParameters() { return m_parameters; }

		//! Set the parameters of the window and system.
        /*!
        	This function will only recreate the window and change the .ini, but not reload the lang if changed.
        	\param parameters Parameters of the game.
        */
		void SetParameters(GameParameters parameters);

	private:
		bool checkIni();

		std::vector<GameState *> m_states;
		sf::RenderWindow * m_window;
		bool m_running;

		std::string m_title;

		GameParameters m_parameters;
};

}

#endif

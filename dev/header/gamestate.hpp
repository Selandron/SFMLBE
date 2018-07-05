#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

/*!
    \file gamestate.hpp
    \brief Describe a Game State class.
    \author Etienne Andrieu
    \version 1.0
 */

#include "gamemanager.hpp"

namespace sfmlbe
{

/*!
    Virtual class representing a GameState. Need to be inherit to be used with the GameManager.
*/
class GameState
{
	public:
		//! Virtual member. Init the state.
        /*!
            \sa Unload()
        */
		virtual void Init(GameManager * game) = 0;

		//! Virtual member. Cleanup the memory in the state.
        /*!
        	\sa Cleanup()
        */
		virtual void Cleanup() = 0;

		//! Virtual member. Pause the state.
        /*!
        	\sa Resume()
        */
		virtual void Pause() = 0;

		//! Virtual member. Resume the state.
        /*!
        	\sa Pause()
        */
		virtual void Resume() = 0;

		//! Virtual member. Handle the poll event loop.
        /*!
        	\param game GameManager that can be used.
            \sa Update(GameManager * game) and Draw(GameManager * game)
        */
		virtual void HandleEvents(GameManager * game) = 0;

		//! Virtual member. Update what to display.
        /*!
        	\param game GameManager that can be used.
            \sa HandleEvents(GameManager * game) and Draw(GameManager * game)
        */
		virtual void Update(GameManager * game) = 0;

		//! Virtual member. Draw what to draw.
        /*!
        	\param game GameManager that can be used.
            \sa HandleEvents(GameManager * game) and Update(GameManager * game)
        */
		virtual void Draw(GameManager * game) = 0;

		//! Change the actual state.
        /*!
        	\param game GameManager that will call the state.
        	\param state GameState that will be called.
        */
		void ChangeState(GameManager* game, GameState* state) { game->ChangeState(state); }

	protected:
		//! Constructor.
        /*!
            Construct GameState.
        */
		GameState() { }
};

}

#endif
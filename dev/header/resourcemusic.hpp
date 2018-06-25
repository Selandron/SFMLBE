#ifndef RESOURCE_MUSIC_HPP
#define RESOURCE_MUSIC_HPP

/*!
    \file resourcemusic.hpp
    \brief Represent a resource storing a music.
    \author Etienne Andrieu
    \version 1.0
 */

#include "resource.hpp"
#include <SFML/Audio.hpp>

namespace sfmlbe 
{

/*!
	Class allowing to store a sf::Music using the SFMLBE Resource Manager system.
	Provide an interface to load and unload music easily.
 */
class ResourceMusic : public Resource
{
	public:
		//! Constructor.
        /*!
            Construct a non loaded music resource.
            \sa ResourceMusic(std::string ID, std::string filename) and ~ResourceMusic()
        */
		ResourceMusic();

		//! Constructor.
        /*!
            Construct a non loaded music resource, but with provided parameters.
            \param ID ID of the resource in the scope specified.
            \param filename Relative path of file from where the resource is loaded.
            \sa ResourceMusic() and ~ResourceMusic()
        */
		ResourceMusic(std::string ID, std::string filename);

		//! Descructor.
        /*!
        	Free memory used by the sf::Music and this resource.
            \sa ResourceMusic() and ResourceMusic(std::string ID, std::string filename)
        */
		~ResourceMusic();

		//! Load the sf::Music targeted by this resource.
        /*!
        	If success set this resource as loaded.
            \sa Unload() and IsLoaded()
        */
		void Load();

		//! Unload the sf::Music targeted by this resource.
        /*!
        	If success set this resource as unloaded.
            \sa Load() and IsLoaded()
        */
        void Unload();

		//! Get the sf::Music associed to this resource.
        /*!
            \return Reference to the sf::Music or NULL.
        */
		sf::Music * GetMusic() {return m_music;}

	private:
		sf::Music * m_music;
};

}
#endif
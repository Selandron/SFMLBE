#ifndef RESOURCE_SOUNDBUFFER_HPP
#define RESOURCE_SOUNDBUFFER_HPP

/*!
    \file resourcesoundbuffer.hpp
    \brief Represent a resource storing a soundbuffer.
    \author Etienne Andrieu
    \version 1.0
 */

#include "resource.hpp"
#include <SFML/Audio.hpp>

namespace sfmlbe 
{

/*!
	Class allowing to store a sf::SoundBuffer using the SFMLBE Resource Manager system.
	Provide an interface to load and unload soundbuffer easily.
 */
class ResourceSoundBuffer : public Resource
{
	public:
		//! Constructor.
        /*!
            Construct a non loaded soundbuffer resource.
            \sa ResourceSoundBuffer(std::string ID, std::string filename) and ~ResourceSoundBuffer()
        */
		ResourceSoundBuffer();

		//! Constructor.
        /*!
            Construct a non loaded soundbuffer resource, but with provided parameters.
            \param ID ID of the resource in the scope specified.
            \param filename Relative path of file from where the resource is loaded.
            \sa ResourceSoundBuffer() and ~ResourceSoundBuffer()
        */
		ResourceSoundBuffer(std::string ID, std::string filename);

		//! Descructor.
        /*!
        	Free memory used by the sf::SoundBuffer and this resource.
            \sa ResourceSoundBuffer() and ResourceSoundBuffer(std::string ID, std::string filename)
        */
		~ResourceSoundBuffer();

		//! Load the sf::SoundBuffer targeted by this resource.
        /*!
        	If success set this resource as loaded.
            \sa Unload() and IsLoaded()
        */
		void Load();

		//! Unload the sf::SoundBuffer targeted by this resource.
        /*!
        	If success set this resource as unloaded.
            \sa Load() and IsLoaded()
        */
        void Unload();

        //! Get the sf::SoundBuffer associed to this resource.
        /*!
            \return Reference to the sf::SoundBuffer or NULL.
        */
		sf::SoundBuffer * GetSoundBuffer() {return m_soundBuffer;}
		
	private:
		sf::SoundBuffer * m_soundBuffer;
};

}
#endif
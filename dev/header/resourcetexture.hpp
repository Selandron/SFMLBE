#ifndef RESOURCETEXTURE_HPP
#define RESOURCETEXTURE_HPP

/*!
    \file resourcetexture.hpp
    \brief Represent a resource storing a texture.
    \author Etienne Andrieu
    \version 1.0
 */

#include "resource.hpp"
#include <SFML/Graphics.hpp>

namespace sfmlbe 
{

/*!
	Class allowing to store a sf::Texture using the SFMLBE Resource Manager system.
	Provide an interface to load and unload texture easily.
 */
class ResourceTexture : public Resource
{
	public:
		//! Constructor.
        /*!
            Construct a non loaded texture resource.
            \sa ResourceTexture(std::string ID, std::string filename) and ~ResourceTexture()
        */
		ResourceTexture();

		//! Constructor.
        /*!
            Construct a non loaded texture resource, but with provided parameters.
            \param ID ID of the resource in the scope specified.
            \param filename Relative path of file from where the resource is loaded.
            \sa ResourceTexture() and ~ResourceTexture()
        */
		ResourceTexture(std::string ID, std::string filename);

		//! Descructor.
        /*!
        	Free memory used by the sf::Texture and this resource.
            \sa ResourceTexture() and ResourceTexture(std::string ID, std::string filename)
        */
		~ResourceTexture();

		//! Load the sf::Texture targeted by this resource.
        /*!
        	If success set this resource as loaded.
            \sa Unload() and IsLoaded()
        */
		void Load();

		//! Unload the sf::Texture targeted by this resource.
        /*!
        	If success set this resource as unloaded.
            \sa Load() and IsLoaded()
        */
        void Unload();

        //! Get the sf::Texture associed to this resource.
        /*!
            \return Reference to the sf::Texture or NULL.
        */
		sf::Texture * GetTexture() {return m_texture;}
        
	private:
		sf::Texture * m_texture;
};

}
#endif
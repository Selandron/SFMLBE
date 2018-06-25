#ifndef RESOURCE_FONT_HPP
#define RESOURCE_FONT_HPP

/*!
    \file resourcefont.hpp
    \brief Represent a resource storing a font.
    \author Etienne Andrieu
    \version 1.0
 */

#include "resource.hpp"
#include <SFML/Graphics.hpp>

namespace sfmlbe
{

/*!
	Class allowing to store a sf::Font using the SFMLBE Resource Manager system.
	Provide an interface to load and unload font easily.
 */
class ResourceFont : public Resource
{
	public:
		//! Constructor.
        /*!
            Construct a non loaded font resource.
            \sa ResourceFont(std::string ID, std::string filename) and ~ResourceFont()
        */
		ResourceFont();

		//! Constructor.
        /*!
            Construct a non loaded font resource, but with provided parameters.
            \param ID ID of the resource in the scope specified.
            \param filename Relative path of file from where the resource is loaded.
            \sa ResourceFont() and ~ResourceFont()
        */
		ResourceFont(std::string ID, std::string filename);

		//! Descructor.
        /*!
        	Free memory used by the sf::Font and this resource.
            \sa ResourceFont() and ResourceFont(std::string ID, std::string filename)
        */
		~ResourceFont();

		//! Load the sf::Font targeted by this resource.
        /*!
        	If success set this resource as loaded.
            \sa Unload() and IsLoaded()
        */
		void Load();

		//! Unload the sf::Font targeted by this resource.
        /*!
        	If success set this resource as unloaded.
            \sa Load() and IsLoaded()
        */
        void Unload();

        //! Get the sf::Font associed to this resource.
        /*!
            \return Reference to the sf::Font or NULL.
        */
		sf::Font * GetFont() {return m_font;}

	private:
		sf::Font * m_font;
};

}
#endif
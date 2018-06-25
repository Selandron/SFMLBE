#ifndef RESOURCE_TEXT_HPP
#define RESOURCE_TEXT_HPP

/*!
    \file resourcetext.hpp
    \brief Represent a resource storing texts.
    \author Etienne Andrieu
    \version 1.0
 */

#include "resource.hpp"
#include "tinyxml2.hpp"
#include <iostream>
#include <string>
#include <map>

namespace sfmlbe
{

/*!
	Class allowing to store a std::map of std::string using the SFMLBE Resource Manager system.
	Provide an interface to load and unload large texts easily.
 */
class ResourceText : public Resource
{
	public:
		//! Constructor.
        /*!
            Construct a non loaded text resource.
            \sa ResourceText(std::string ID, std::string filename) and ~ResourceText()
        */
		ResourceText();

		//! Constructor.
        /*!
            Construct a non loaded text resource, but with provided parameters.
            \param ID ID of the resource in the scope specified.
            \param filename Relative path of file from where the resource is loaded.
            \sa ResourceText() and ~ResourceText()
        */
		ResourceText(std::string ID, std::string filename);

		//! Descructor.
        /*!
        	Free memory used by all the strings and this resource.
            \sa ResourceText() and ResourceText(std::string ID, std::string filename)
        */
		~ResourceText();

		//! Load the std::map of the std::string targeted by this resource.
        /*!
        	If success set this resource as loaded.
            \sa Unload() and IsLoaded()
        */
		void Load();

		//! Unload the std::map of the std::string targeted by this resource.
        /*!
        	If success set this resource as unloaded.
            \sa Load() and IsLoaded()
        */
        void Unload();

        //! Get the std::map of the std::string associed to this resource, with a key needed.
        /*!
        	\param key Key of the std::string wanted.
            \return Reference to the sf::map or NULL.
        */
		std::string * GetText(std::string key);

	private:
		std::map<std::string, std::string *> * m_resources;
};

}
#endif
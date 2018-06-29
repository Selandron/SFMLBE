#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

/*!
    \file resourcemanager.hpp
    \brief Handle every resources loaded, accessible anywhere in the prgramme using Singleton pattern.
    \author Etienne Andrieu
    \version 1.0
 */

#include "resource.hpp"
#include "resourcetexture.hpp"
#include "resourcesoundbuffer.hpp"
#include "resourcemusic.hpp"
#include "resourcefont.hpp"
#include "resourcetext.hpp"
#include "singleton.hpp"
#include "resourceexceptions.hpp"
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "tinyxml2.hpp"

namespace sfmlbe
{

/*!
	Class representing a Manager for all the resources.
	Provide an interface to load and unload resources easily, and to retreive them from anywhere.
	Use a scope system to provide multiple occurences of a resource and manage multiple contexts easier.
 */
class ResourceManager : public sfmlbe::Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;

	public:
		//! Get a reference on the Resource requested.
        /*!
        	Return the first occurrence of the Resource requested in all scopes loaded. Resource could be any type listed in RESOURCE_TYPE.
        	\throw sfmlbe::ResourceNotFoundException if the resource is not found in any scope.
        	\param ID ID of the resource .
        	\return Reference on the sfmlbe::Resource or throws exception.
            \sa FindResourceByID(const std::string & ID, const std::string & scope)
        */
		Resource * FindResourceByID(const std::string & ID);

		//! Get a reference on the Resource requested.
        /*!
        	Return the occurence of the Resource requested in the scope targeted. Resource could be any type listed in RESOURCE_TYPE.
        	\throw sfmlbe::ResourceNotFoundException if the resource is not found in the scope.
        	\throw sfmlbe::ScopeNotFoundException if the scope is not found.
        	\param ID ID of the resource.
        	\param scope Name of the scope where to search the resource.
        	\return Reference on the sfmlbe::Resource or throws exception.
            \sa FindResourceByID(const std::string & ID)
        */
		Resource * FindResourceByID(const std::string & ID, const std::string & scope);

		//! Clear the scope targeted.
        /*!
        	Free memory for all the resources in the scope, and delete it.
        	If he does not exist, do nothing. 
        	\param scopename Name of the scope to clear.
            \sa Clear()
        */
		void ClearScope(const std::string & scopename);

		//! Clear all the scopes.
        /*!
        	Free memory for all the resources in all scopes, and delete everthing.
        	Reset the ResourceManager. 
            \sa Clear(const std::string & scopename)
        */
		void Clear();

		//! Load Resource indexed in the XML file targeted.
        /*!
        	Try to load every resource indexed in the filename in the first valid scope.
        	Creates the scope or appends the resources if the scope already exists. If some identical keys are already in it, they will be replaced !
        	Filename and resources need to be in the data folder (see examples).
        	\param filename Name of the indexer where all the resources are listes.
            \sa LoadFromFileXML(const std::string & filename, const std::string & scopename) and LoadFromFileXML(const std::string & filename, const std::string & scopename, const std::string & scope_target)
        */
		void LoadFromFileXML(const std::string & filename);

		//! Load Resource indexed in the XML file targeted with a targeted scope.
        /*!
        	Try to load every resource indexed in the filename in the targeted scope.
        	Creates the scope or appends the resources if the scope already exists. If some identical keys are already in it, they will be replaced !
        	Filename and resources need to be in the data folder (see examples).
        	\param filename Name of the indexer where all the resources are listes.
        	\param scopename Name of the scope wanted in filename.
            \sa LoadFromFileXML() and LoadFromFileXML(const std::string & filename, const std::string & scopename, const std::string & scope_target)
        */
		void LoadFromFileXML(const std::string & filename, const std::string & scopename);

		//! Load Resource indexed in the XML file targeted with a targeted scope and add them to another scope.
        /*!
        	Try to load every resource indexed in the filename in the targeted scope and append them to anoter scope.
        	Creates the scope targeted or appends the resources if the scope already exists. If some identical keys are already in it, they will be replaced !
        	Filename and resources need to be in the data folder (see examples).
        	\param filename Name of the indexer where all the resources are listes.
        	\param scopename Name of the scope wanted in filename.
        	\param scope_target Name of the scope where append resources.
            \sa LoadFromFileXML() and LoadFromFileXML(const std::string & filename, const std::string & scopename)
        */
		void LoadFromFileXML(const std::string & filename, const std::string & scopename, const std::string & scope_target);

		//! Print all the resources in the Resource Manager.
        /*!
        	Do what it says.
        */
		void PrintManager();

		//! Get the number of resources loaded.
        /*!
        	\return Number of resources loaded.
        */
		UINT GetResourceCount() const { return m_resourceCount; }

	private:
		//! Constructor.
        /*!
            Construct ResourceManager. Only called once in singleton.
            \sa ~ResourceManager()
        */
		ResourceManager() : m_resourceCount(0) {};

		//! Destructor.
        /*!
            Destruct ResourceManager.
            \sa ResourceManager()
        */
		~ResourceManager() {Clear();};

		//! Recursive function to parse XML tree.
        /*!
            \param root Reference on the XMLNode where the parsing will begin.
			\param path Current path of the file in before the node.
        */
		void ParseXMLTree(tinyxml2::XMLNode * root, std::string path);

		//! Function that create the resource associeted to the element.
        /*!
            \param element XML element where the information will be taken to construct the sfmlbe::Resource.
			\param path Current path of the file in before the element.
			\return A reference on the resource (non loaded) created.
			\throw sfmlbe::ResourceNotLoadException if the resource was not created.
        */
		tr::Resource * CreateResource(const tinyxml2::XMLElement * element, const std::string & path);

		//! Load the resources that are not already loaded
        /*!
            \param scope_target Scope where to append the sfmlbe::Resources
        */
		void LoadPendingResources(const std::string & scope_target);

		std::vector<Resource *> m_listOfPendingResources;							//Resources creates but not stored
		UINT m_resourceCount; 														//Total number of resources loaded
	    std::map<std::string, std::map<std::string, Resource *> * > m_resources; 	//Map of form <scope ID, Resource map>
};

}

#endif
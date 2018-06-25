#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

/*
    Resource Manager. Handle every resource loaded.
    You have to passe by a (or more) xml file that indexes every resource.

    Author : Etienne Andrieu
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

class ResourceManager : public sfmlbe::Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;	//Set Singleton system

	public:
		Resource * FindResourceByID(const std::string & ID);								//Get the resource wanted
		Resource * FindResourceByID(const std::string & ID, const std::string & scope);		//Get the resource wanted in the scope targeted
		void ClearScope(const std::string & scopename);										//Empty the resources for a define scope
		void Clear();																		//Empty ALL the resources (careful with the use)
		void LoadFromFileXML(const std::string & filename);									//Load an XML file (in data folder) to parse resources (first scope)
		void LoadFromFileXML(const std::string & filename, const std::string & scopename);	//Load an XML file (in data folder) with a scope wanted to parse resources
		void PrintManager();																//Print all content from the manager
		UINT GetResourceCount() const { return m_resourceCount; }							//Get the number of resources stored
	protected:
	    UINT m_resourceCount; 																//Total number of resources loaded
	    std::map<std::string, std::map<std::string, Resource *> * > m_resources; 			//Map of form <scope ID, Resource map>

	private:
		ResourceManager() : m_resourceCount(0) {};																	//Private Constructor (only called once in Singleton)
		~ResourceManager() {};																						//Private Destructor (only called once)

		void ParseXMLTree(tinyxml2::XMLNode * root, std::string path);												//Recursive function to parse XML tree
		Resource * CreateResource(const tinyxml2::XMLElement * element, const std::string & path); 				//Function to create (but not load) resource
		void LoadPendingResources(std::string & scope);																//Load the resources not alreadys loaded

		std::vector<Resource *> m_listOfPendingResources;															//Resources creates but not stored
};

}

#endif
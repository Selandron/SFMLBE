#include "sfmlbe.hpp"


sfmlbe::ResourceFont::ResourceFont()
: sfmlbe::Resource("null_font", "null_font")
{
	m_type = RESOURCE_FONT;
	m_font = NULL;
}

sfmlbe::ResourceFont::ResourceFont(std::string id, std::string filename)
: sfmlbe::Resource(id, filename)
{	
	m_type = RESOURCE_FONT;
}

sfmlbe::ResourceFont::~ResourceFont()
{
	Unload();
}

void sfmlbe::ResourceFont::Load()
{
	m_font = new sf::Font();
	if (!m_font->loadFromFile(m_filename))
	    m_loaded = false;
	else 
		m_loaded = true;
}

void sfmlbe::ResourceFont::Unload()
{
	if (m_font)
		delete m_font;
	m_loaded = false;
}

sfmlbe::ResourceMusic::ResourceMusic()
: sfmlbe::Resource("null_music", "null_music")
{
	m_type = RESOURCE_MUSIC;
	m_music = NULL;
}

sfmlbe::ResourceMusic::ResourceMusic(std::string id, std::string filename)
: sfmlbe::Resource(id, filename)
{	
	m_type = RESOURCE_MUSIC;
}

sfmlbe::ResourceMusic::~ResourceMusic()
{
	Unload();
}

void sfmlbe::ResourceMusic::Load()
{
	m_music = new sf::Music();
	if (!m_music->openFromFile(m_filename))
	    m_loaded = false;
	else 
		m_loaded = true;
}

void sfmlbe::ResourceMusic::Unload()
{
	if (m_music != NULL)
		delete m_music;
	m_loaded = false;
}

sfmlbe::ResourceSoundBuffer::ResourceSoundBuffer()
: sfmlbe::Resource("null_soundbuffer", "null_soundbuffer")
{
	m_type = RESOURCE_SOUNDBUFFER;
	m_soundBuffer = NULL;
}

sfmlbe::ResourceSoundBuffer::ResourceSoundBuffer(std::string id, std::string filename)
: sfmlbe::Resource(id, filename)
{	
	m_type = RESOURCE_SOUNDBUFFER;
}

sfmlbe::ResourceSoundBuffer::~ResourceSoundBuffer()
{
	Unload();
}

void sfmlbe::ResourceSoundBuffer::Load()
{
	m_soundBuffer = new sf::SoundBuffer();
	if (!m_soundBuffer->loadFromFile(m_filename))
	    m_loaded = false;
	else 
		m_loaded = true;
}

void sfmlbe::ResourceSoundBuffer::Unload()
{
	if (m_soundBuffer)
		delete m_soundBuffer;
	m_loaded = false;
}

sfmlbe::ResourceText::ResourceText()
: sfmlbe::Resource("null_string", "null_string")
{
	m_type = RESOURCE_TEXT;
	m_resources = NULL;
}

sfmlbe::ResourceText::ResourceText(std::string id, std::string filename)
: sfmlbe::Resource(id, filename)
{	
	m_type = RESOURCE_TEXT;
}

sfmlbe::ResourceText::~ResourceText()
{
	Unload();
}

void sfmlbe::ResourceText::Load()
{
	m_resources = new std::map<std::string, std::string *>();

	tinyxml2::XMLDocument doc;
	doc.LoadFile(m_filename.c_str());
	if (doc.Error())
	{	
		std::cerr << doc.ErrorStr() << std::endl;
		delete m_resources;
		m_loaded = false;
		return;
	}

	tinyxml2::XMLElement * root = doc.FirstChildElement();

	if (strcmp(root->Value(), "text") == 0 && root->Attribute("key") != NULL)
	{
		std::string * str = new std::string(root->GetText());
		m_resources->insert(std::pair<std::string, std::string *>(root->Attribute("key"), str));
	}
	while(root->NextSiblingElement("text") != NULL)
	{
		root = root->NextSiblingElement("text");
		if (strcmp(root->Value(), "text") == 0 && root->Attribute("key") != NULL)
		{
			std::string * str = new std::string(root->GetText());
			m_resources->insert(std::pair<std::string, std::string *>(root->Attribute("key"), str));
		}
	}

	if (!m_resources) 
	    m_loaded = false;
	else 
		m_loaded = true;
}

void sfmlbe::ResourceText::Unload()
{
	if (m_resources)
	{
		for(auto& it: *m_resources)
			delete it.second;
		m_resources->clear();
	}
	delete m_resources;
	m_loaded = false;
}

std::string * sfmlbe::ResourceText::GetText(std::string key)
{
	if (!m_loaded)
		return NULL;
	for (auto& it: *m_resources)
		if (it.first.compare(key) == 0)
			return it.second;
	return NULL;
}

sfmlbe::ResourceTexture::ResourceTexture()
: sfmlbe::Resource("null_graphic", "null_graphic")
{
	m_type = RESOURCE_GRAPHIC;
	m_texture = NULL;
}

sfmlbe::ResourceTexture::ResourceTexture(std::string id, std::string filename)
: sfmlbe::Resource(id, filename)
{	
	m_type = RESOURCE_GRAPHIC;
}

sfmlbe::ResourceTexture::~ResourceTexture()
{
	Unload();
}

void sfmlbe::ResourceTexture::Load()
{
	m_texture = new sf::Texture();
	if (!m_texture->loadFromFile(m_filename))
	    m_loaded = false;
	else 
		m_loaded = true;
}

void sfmlbe::ResourceTexture::Unload()
{
	if (m_texture != NULL)
		delete m_texture;
	m_loaded = false;
}

sfmlbe::Resource * sfmlbe::ResourceManager::FindResourceByID(const std::string & ID) 
{
	for (std::map<std::string,std::map<std::string, sfmlbe::Resource *> * >::iterator it = this->m_resources.begin(); it != this->m_resources.end(); ++it)
		if (FindResourceByID(ID, it->first))
			return FindResourceByID(ID, it->first);
	throw sfmlbe::ResourceNotFoundException(ID.c_str());
}

sfmlbe::Resource * sfmlbe::ResourceManager::FindResourceByID(const std::string & ID, const std::string & scope)
{
	std::map<std::string,std::map<std::string, sfmlbe::Resource *> * >::iterator it = this->m_resources.find(scope);
	if (it == this->m_resources.end())
		throw sfmlbe::ScopeNotFoundException(scope.c_str());
	std::map<std::string, sfmlbe::Resource *>::iterator sub = it->second->find(ID);
	return ((sub == it->second->end()) ? throw sfmlbe::ResourceNotFoundException(ID.c_str()) : sub->second);
}

void sfmlbe::ResourceManager::LoadFromFileXML(const std::string & filename)
{
	//Opening XML document
	tinyxml2::XMLDocument doc;
	std::string root = "./data/";
	root += filename;
	doc.LoadFile(root.c_str());
	if (doc.Error()) //Error while pre-parsing document
	{	
		std::cerr << doc.ErrorStr() << std::endl;
		return;
	}

	tinyxml2::XMLElement * scopeEl = doc.FirstChildElement("scope"); //Get the first scope name
	if (scopeEl && scopeEl->Attribute("name") != NULL && !scopeEl->NoChildren())		
	{
		std::string scope = scopeEl->Attribute("name");
		LoadFromFileXML(filename, scope, scope);	//Call for the generic function
	}
	else if (!scopeEl)	//Handles errors
		std::cerr << "Error : " << filename << " There is no scope in this file." << std::endl;
	else if (scopeEl->NoChildren() && scopeEl->Attribute("name") != NULL)
		std::cerr << "Error : In " << filename << " scope " << scopeEl->Attribute("name") << " has no resources indexed!" << std::endl;
	else		
		std::cerr << "Error : " << filename << " - Unknow Error." << std::endl;
}

void sfmlbe::ResourceManager::LoadFromFileXML(const std::string & filename, const std::string & scopename)
{
	//Opening XML document
	tinyxml2::XMLDocument doc;
	std::string root = "./data/";
	root += filename;
	doc.LoadFile(root.c_str());
	if (doc.Error()) //Error while pre-parsing document
	{	
		std::cerr << doc.ErrorStr() << std::endl;
		return;
	}

	//PARSING
	std::string path = "./data/";	//Root path

	//Search the good scope
	tinyxml2::XMLNode * scopeSearch = doc.FirstChild()->NextSibling();
	tinyxml2 ::XMLElement * scopeEl;
	while (scopeSearch != NULL)
	{
		scopeEl = scopeSearch->ToElement();
		if (scopeEl && strcmp(scopeEl->Value(), "scope") == 0 && strcmp(scopeEl->Attribute("name"), scopename.c_str()) == 0)
			break;
		else
			scopeSearch = scopeEl->NextSibling(); 
	}
	if (scopeSearch == NULL)
		scopeEl = NULL;

	if (scopeEl && !scopeEl->NoChildren()) //If we have a good scope	
	{
		std::string scope = scopeEl->Attribute("name");
		LoadFromFileXML(filename, scope, scope);	//Call for the generic function
	}
	else if (!scopeEl)	//Handle errors
		std::cerr << "Error : " << filename << " - scope name " << scopename << " don't exist." << std::endl;
	else if (scopeEl->NoChildren())
		std::cerr << "Error : In " << filename << " scope " << scopename << " has no resources indexed!" << std::endl;
	else
		std::cerr << "Error : " << filename << " - Unknown Error from " << scopename << "." << std::endl;
}

void sfmlbe::ResourceManager::LoadFromFileXML(const std::string & filename, const std::string & scopename, const std::string & scope_target)
{
	//Opening XML document
	tinyxml2::XMLDocument doc;
	std::string root = "./data/";
	root += filename;
	doc.LoadFile(root.c_str());
	if (doc.Error()) //Error while pre-parsing document
	{	
		std::cerr << doc.ErrorStr() << std::endl;
		return;
	}

	//PARSING
	std::string path = "./data/";	//Root path

	//Search the good scope
	tinyxml2::XMLNode * scopeSearch = doc.FirstChild()->NextSibling();
	tinyxml2 ::XMLElement * scopeEl;
	while (scopeSearch != NULL)
	{
		scopeEl = scopeSearch->ToElement();
		if (scopeEl && strcmp(scopeEl->Value(), "scope") == 0 && strcmp(scopeEl->Attribute("name"), scopename.c_str()) == 0)
			break;
		else
			scopeSearch = scopeEl->NextSibling(); 
	}
	if (scopeSearch == NULL)
		scopeEl = NULL;

	if (scopeEl && !scopeEl->NoChildren()) //If we have a good scope	
	{
		std::string scope = scopeEl->Attribute("name");
		ParseXMLTree(scopeEl, path); //Parse the XML Tree while creating Resources
		LoadPendingResources(scope_target);  //Load the pending Resources stored
	}
	else if (!scopeEl)	//Handle errors
		std::cerr << "Error : " << filename << " - scope name " << scopename << " don't exist." << std::endl;
	else if (scopeEl->NoChildren())
		std::cerr << "Error : In " << filename << " scope " << scopename << " has no resources indexed!" << std::endl;
	else
		std::cerr << "Error : " << filename << " - Unknown Error from " << scopename << "." << std::endl;
}

void sfmlbe::ResourceManager::ParseXMLTree(tinyxml2::XMLNode * root, std::string path)
{
	tinyxml2::XMLNode * childNode = root->FirstChildElement();
	while (childNode)	//While the root node have childs
	{
		if (strcmp(childNode->Value(), "file") == 0)	//If its a file
		{
			tinyxml2::XMLElement * element = childNode->ToElement();
			if (element && element->Attribute("key") && element->Attribute("type") && element->GetText()) //Has enough attributes
			{									
				std::string key = element->Attribute("key");
				try
				{
					sfmlbe::Resource * t = CreateResource(element, path);	//Create of the Resource	
					m_listOfPendingResources.push_back(t);	//Store the Resource for loading
				}
				catch (sfmlbe::ResourceNotLoadException & e)
				{
					std::cout << e.what() << std::endl;
				}
			}
		}
		else 											//If not, recursive loading
		{
			std::string newPath = path;
			newPath += childNode->Value();
			newPath += "/";
			ParseXMLTree(childNode, newPath); //Parse the XML Tree while creating resources
		}
		childNode = childNode->NextSibling();
	}
}

sfmlbe::Resource * sfmlbe::ResourceManager::CreateResource(const tinyxml2::XMLElement * element, const std::string & path)
{
	std::string key = element->Attribute("key"); //Get all parameters needed
	std::string file = element->GetText();
	file = path  + file;
	RESOURCE_TYPE type = (RESOURCE_TYPE)element->IntAttribute("type");
	Resource * r;

	switch(type) //Create the good type of resource
	{
		case RESOURCE_TYPE::RESOURCE_GRAPHIC: 
			r = new ResourceTexture(key, file);
			break;
		case RESOURCE_TYPE::RESOURCE_SOUNDBUFFER:
			r = new ResourceSoundBuffer(key, file);
			break;
		case RESOURCE_TYPE::RESOURCE_MUSIC:
			r = new ResourceMusic(key, file);
			break;
		case RESOURCE_TYPE::RESOURCE_FONT:
			r = new ResourceFont(key, file);
			break;
		case RESOURCE_TYPE::RESOURCE_TEXT:
			r = new ResourceText(key, file);
			break;
		default:
			throw sfmlbe::ResourceNotLoadException(file.c_str());
	}

	if (r)
		return r;
	else
		throw sfmlbe::ResourceNotLoadException(file.c_str());
}

bool sortByType(sfmlbe::Resource *& r1, sfmlbe::Resource *& r2) { return ((int)r1->GetResourceType() < (int)r2->GetResourceType()); } //Function used to sorts Resources by their types

void sfmlbe::ResourceManager::LoadPendingResources(const std::string & scope_target)
{ 
	std::sort(m_listOfPendingResources.begin(), m_listOfPendingResources.end(), sortByType); //Sort the resources to load by their types
	std::map<std::string, Resource *> * dup = new std::map<std::string, Resource *>();
	for (unsigned int i = 0; i < m_listOfPendingResources.size(); ++i)	//Load each resources
	{
		try
		{
			Resource * r = m_listOfPendingResources[i];
			if (r)
			{
				r->Load();
				if (!r->IsLoaded())
				{
					delete r;
					throw sfmlbe::ResourceNotLoadException(r->GetFilename().c_str());
				}
				dup->insert(std::pair<std::string, sfmlbe::Resource *>(r->GetResourceID(), r)); //Insert the resource
				this->m_resourceCount++;
				float progress = (float)(i) / (float)m_listOfPendingResources.size(); //Display progress
			    int barWidth = 40;
			    std::cout << "[";
			    int pos = barWidth * progress;
			    for (int i = 0; i < barWidth; ++i) {
			        if (i < pos) std::cout << "=";
			        else if (i == pos) std::cout << ">";
			        else std::cout << " ";
			    }
			    std::cout << "] " << int(progress * 100.0) << " %\r";
			    std::cout.flush();
			}
		}
		catch (ResourceNotLoadException & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	m_listOfPendingResources.clear(); //Clear the list of pending resources

	float progress = 1.0; //Display max bar progress
	int barWidth = 40;
	std::cout << "[";
	int pos = barWidth * progress;
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) std::cout << "=";
		else if (i == pos) std::cout << ">";
		else std::cout << " ";
	}
	std::cout << "] " << int(progress * 100.0) << " %\r";
	std::cout.flush();
	std::cout << std::endl;

	if (dup->size() != 0) // If some resources still have been loaded
	{
		std::map<std::string,std::map<std::string, sfmlbe::Resource *> * >::iterator it = this->m_resources.find(scope_target);
		if (it != this->m_resources.end()) //If a scope with that name already exist append to the scope
		{
			for (std::map<std::string, Resource *>::iterator i = dup->begin(); i != dup->end(); ++i)
			{
				if (it->second->find(i->first) != it->second->end())
				{
					delete (it->second->find(i->first))->second;
					it->second->find(i->first)->second = i->second;
				}
				else
				{
					it->second->insert(std::pair<std::string, Resource *>(i->first, i->second));
					this->m_resourceCount++;
				}
			}
			delete dup;
		}
		else //If not, insert only
		{
			this->m_resources.insert(std::pair<std::string, std::map<std::string, Resource *> * >(scope_target, dup)); //Insert the resource scope
			this->m_resourceCount += dup->size();
		}
	}
	else
		delete dup;
}

void sfmlbe::ResourceManager::Clear()
{
	for (std::map<std::string,std::map<std::string, sfmlbe::Resource *> * >::iterator it = this->m_resources.begin(); it != this->m_resources.end(); ++it)
		ClearScope(it->first);
	this->m_resources.clear();
	this->m_resourceCount = 0;
}

void sfmlbe::ResourceManager::ClearScope(const std::string & scope)
{
	std::map<std::string,std::map<std::string, sfmlbe::Resource *> * >::iterator it = this->m_resources.find(scope); 	//Iterator on the map

	if (it == this->m_resources.end()) //If not found, OK
		return;

	//If found, remove all in sub map (free memory)
	std::map<std::string, sfmlbe::Resource *> * resourcesMap = it->second;
	for (std::map<std::string, sfmlbe::Resource *>::iterator sub = resourcesMap->begin(); sub != resourcesMap->end(); ++sub)
	{
		if (sub->second)
			delete sub->second;
		this->m_resourceCount--;
	}
	resourcesMap->clear();
	delete resourcesMap;
	this->m_resources.erase(it); //Remove in first map the entry 
}

void sfmlbe::ResourceManager::PrintManager()
{
	if (this->m_resources.size() == 0)
		std::cout << "No resources" << std::endl;
	for (std::map<std::string,std::map<std::string, sfmlbe::Resource *> * >::iterator it = this->m_resources.begin(); it != this->m_resources.end(); it++)
	{
		std::cout << "Scope : " << it->first << std::endl;
		std::map<std::string, sfmlbe::Resource *> * resourcesMap = it->second;
		std::vector<sfmlbe::Resource * > listResources;
		for (std::map<std::string, sfmlbe::Resource *>::iterator sub = resourcesMap->begin(); sub != resourcesMap->end(); ++sub)
			listResources.push_back(sub->second);
		std::sort(listResources.begin(), listResources.end(), sortByType);
		for (std::vector<sfmlbe::Resource *>::iterator sub = listResources.begin(); sub != listResources.end(); sub++)
		{
			Resource * r = *sub;
			std::cout << "\t-- Key : " << r->GetResourceID() << " -- Target : " << r->GetFilename() << " -- Type : ";
			switch (r->GetResourceType())
			{
				case RESOURCE_TYPE::RESOURCE_GRAPHIC:
					std::cout << "GRAPHIC" << std::endl;
					break;
				case RESOURCE_TYPE::RESOURCE_SOUNDBUFFER:
					std::cout << "SOUNDBUFFER" << std::endl;
					break;
				case RESOURCE_TYPE::RESOURCE_MUSIC:
					std::cout << "MUSIC" << std::endl;
					break;
				case RESOURCE_TYPE::RESOURCE_FONT:
					std::cout << "FONT" << std::endl;
					break;
				case RESOURCE_TYPE::RESOURCE_TEXT:
					std::cout << "TEXT" << std::endl;
					break;
				default:
					std::cout << "NULL" << std::endl;
					break;
			}
		}
	}
}
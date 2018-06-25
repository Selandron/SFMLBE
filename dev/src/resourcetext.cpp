#include "resourcetext.hpp"

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
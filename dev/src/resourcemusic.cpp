#include "resourcemusic.hpp"

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
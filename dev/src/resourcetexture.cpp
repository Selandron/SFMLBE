#include "resourcetexture.hpp"

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
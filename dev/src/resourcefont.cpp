#include "resourcefont.hpp"

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
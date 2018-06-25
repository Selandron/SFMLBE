#include "resourcesoundbuffer.hpp"

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
	{
		delete m_soundBuffer,
	    m_loaded = false;
	}
	else 
		m_loaded = true;
}

void sfmlbe::ResourceSoundBuffer::Unload()
{
	if (m_soundBuffer)
		delete m_soundBuffer;
	m_loaded = false;
}
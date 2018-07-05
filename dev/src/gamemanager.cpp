#include "gamemanager.hpp"
#include "gamestate.hpp"

void sfmlbe::GameManager::Init(std::string & title)
{ 
	m_title = title;
	m_running = checkIni();
	if (m_running)
	{
		sf::ContextSettings settings(0, 0, m_parameters.antialiasingLevel);
		if (m_parameters.fullscreen)
			m_window = new sf::RenderWindow(m_parameters.windowCaracts, m_title, sf::Style::Fullscreen, settings);
		else
			m_window = new sf::RenderWindow(m_parameters.windowCaracts, m_title, sf::Style::Default, settings);
		m_window->setVerticalSyncEnabled(m_parameters.verticalSync);
		if (m_parameters.maxFramerate != 0)
		m_window->setFramerateLimit(m_parameters.maxFramerate);
	}
	else
		std::cerr << "Corrupt .ini file. You can delete it, it will be recreated. Check the size of the window, size should be fullscreen compatible (sf::VideoMode)." << std::endl;
	
}

void sfmlbe::GameManager::Cleanup()
{
	while(!m_states.empty())
		PopState();
	if (m_window)
		delete m_window;
}

void sfmlbe::GameManager::ChangeState(GameState* state) 
{
	// cleanup the current state
	if (!m_states.empty()) {
		m_states.back()->Cleanup();
		m_states.pop_back();
	}

	// store and init the new state
	m_states.push_back(state);
	m_states.back()->Init(this);
}

void sfmlbe::GameManager::PushState(GameState* state)
{
	// pause current state
	if ( !m_states.empty() ) {
		m_states.back()->Pause();
	}

	// store and init the new state
	m_states.push_back(state);
	m_states.back()->Init(this);
}

void sfmlbe::GameManager::PopState()
{
	// cleanup the current state
	if ( !m_states.empty() ) {
		m_states.back()->Cleanup();
		m_states.pop_back();
	}

	// resume previous state
	if ( !m_states.empty() ) {
		m_states.back()->Resume();
	}
}


void sfmlbe::GameManager::HandleEvents() 
{
	// let the state handle events
	if (!m_states.empty())
		m_states.back()->HandleEvents(this);
}

void sfmlbe::GameManager::Update() 
{
	// let the state update the game
	if (!m_states.empty())
		m_states.back()->Update(this);
}

void sfmlbe::GameManager::Draw() 
{
	// let the state draw the screen
	if (!m_states.empty())
		m_states.back()->Draw(this);
}

void sfmlbe::GameManager::Quit()
{
	m_running = false;
	if (m_parameters.fullscreen)
	{
		delete m_window;
		sf::ContextSettings settings(0, 0, m_parameters.antialiasingLevel);
		m_window = new sf::RenderWindow(m_parameters.windowCaracts, m_title, sf::Style::Default, settings);
	}
	delete m_window;
}

sf::Vector2u sfmlbe::GameManager::GetSize()
{
	return (this->m_window) ? this->m_window->getSize() : sf::Vector2u(0, 0);
}

bool sfmlbe::GameManager::checkIni()
{
	std::ifstream infile("config.ini");
	if (!infile)
	{
		m_parameters.windowCaracts = sf::VideoMode(800, 600, 32);
		m_parameters.fullscreen = false;
		m_parameters.antialiasingLevel = 0;
		m_parameters.maxFramerate = 60;
		m_parameters.verticalSync = false;
		m_parameters.lang = LANG::EN;
		std::ofstream outfile("config.ini");
		if (!outfile)
			return false;
		outfile << "fullscreen = false" << std::endl << "width = 800" << std::endl << "height = 600" << std::endl << "dpp = 32" << std::endl << "antialiasing = 0" << std::endl << "frameratemax = 60" << std::endl << "verticalsync = false" << std::endl << "lang = 0";
		outfile.close();
		return true;
	}

	std::string line, variable, equal;
	//Fullscreen
	std::getline(infile, line);
	std::istringstream iss(line);
	std::string variableBool;
	if(!(iss >> variable >> equal >> variableBool) || variable.compare("fullscreen") !=  0 || equal.compare("=") != 0 || (variableBool.compare("true") != 0 && variableBool.compare("false") != 0))
		return false;
	m_parameters.fullscreen = (variableBool.compare("true") == 0) ? true : false;

	//Caract window
	std::getline(infile, line);
	iss.clear();
	iss.str(line);
	int width, height, dpp;
	if(!(iss >> variable >> equal >> width) || variable.compare("width") != 0 || equal.compare("=") != 0)
		return false;
	m_parameters.windowCaracts.width = width;
	std::getline(infile, line);
	iss.str(line);
	iss.clear();
	if(!(iss >> variable >> equal >> height) || variable.compare("height") != 0 || equal.compare("=") != 0)
		return false;
	m_parameters.windowCaracts.height = height;
	std::getline(infile, line);
	iss.str(line);
	iss.clear();
	if(!(iss >> variable >> equal >> dpp) || variable.compare("dpp") != 0 || equal.compare("=") != 0)
		return false;
	m_parameters.windowCaracts.bitsPerPixel = dpp;

	//Antialiasing
	int antialiasing;
	std::getline(infile, line);
	iss.str(line);
	iss.clear();
	if(!(iss >> variable >> equal >> antialiasing) || variable.compare("antialiasing") != 0 || equal.compare("=") != 0)
		return false;
	m_parameters.antialiasingLevel = antialiasing;

	//Max framarate
	int framerate;
	std::getline(infile, line);
	iss.str(line);
	iss.clear();
	if(!(iss >> variable >> equal >> framerate) || variable.compare("frameratemax") != 0 || equal.compare("=") != 0)
		return false;
	m_parameters.maxFramerate = framerate;

	//Vertical sync
	std::getline(infile, line);
	iss.str(line);
	iss.clear();
	if(!(iss >> variable >> equal >> variableBool) || variable.compare("verticalsync") != 0 || equal.compare("=") != 0 || (variableBool.compare("true") != 0 && variableBool.compare("false") != 0))
		return false;
	m_parameters.verticalSync = (variableBool.compare("true") == 0) ? true : false;

	//Lang
	int lang;
	std::getline(infile, line);
	iss.str(line);
	iss.clear();
	if(!(iss >> variable >> equal >> lang) || equal.compare("=") != 0)
		return false;

	//Test on variables
	std::vector<sf::VideoMode> listVideoMode = sf::VideoMode::getFullscreenModes();
	bool found = false;
	for (std::vector<sf::VideoMode>::iterator i = listVideoMode.begin(); i != listVideoMode.end(); ++i)
		if (*i == m_parameters.windowCaracts)
		{
			found = true;
			break;
		}
	if (!found)
		return false;

	if (m_parameters.antialiasingLevel < 0 || m_parameters.antialiasingLevel > 10)
		return false;

	if (m_parameters.maxFramerate < 0) 
		return false;

	if (m_parameters.maxFramerate != 0 && m_parameters.verticalSync == true)
		m_parameters.verticalSync = false;

	m_parameters.lang = (sfmlbe::LANG)lang;

	return true;
}

void sfmlbe::GameManager::SetParameters(GameParameters parameters)
{
	m_parameters = parameters;
	std::ofstream outfile("config.ini", std::ios::trunc);
	if (!outfile)
		return;
	sf::ContextSettings settings(0, 0, m_parameters.antialiasingLevel);
	delete m_window;
	if (m_parameters.fullscreen)
		m_window = new sf::RenderWindow(m_parameters.windowCaracts, m_title, sf::Style::Fullscreen, settings);
	else
		m_window = new sf::RenderWindow(m_parameters.windowCaracts, m_title, sf::Style::Default, settings);
	m_window->setVerticalSyncEnabled(m_parameters.verticalSync);
	if (m_parameters.maxFramerate != 0)
	m_window->setFramerateLimit(m_parameters.maxFramerate);
	outfile << "fullscreen = " << ((m_parameters.fullscreen) ? "true" : "false") << std::endl
			<< "width = " << m_parameters.windowCaracts.width << std::endl
			<< "height = " << m_parameters.windowCaracts.height << std::endl
			<< "dpp = " << m_parameters.windowCaracts.bitsPerPixel << std::endl
			<< "antialiasing = " << m_parameters.antialiasingLevel << std::endl
			<< "frameratemax = " << m_parameters.maxFramerate << std::endl
			<< "verticalsync = " << ((m_parameters.verticalSync) ? "true" : "false") << std::endl
			<< "lang = " << (int)m_parameters.lang;
	outfile.close();
}
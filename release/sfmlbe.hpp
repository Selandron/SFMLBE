#ifndef SFMLBE
#define SFMLBE

#include <string>
#include <iostream> 
#include <sstream> 
#include <exception>
#include <map>
#include <fstream>
#include <iomanip>
#include <vector>
#include "tinyxml2.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#define UINT unsigned int

namespace sfmlbe
{

/*! \enum RESOURCE_TYPE
    Enum defining every type of resource possible.
*/
enum RESOURCE_TYPE
{
    RESOURCE_NULL = 0, /*!< Represent a not valid resource. */
    RESOURCE_GRAPHIC = 1, /*!< Represent a texture resource. */
    RESOURCE_SOUNDBUFFER = 2, /*!< Represent a soundbuffer resource. */
    RESOURCE_MUSIC = 3, /*!< Represent a music resource. */
    RESOURCE_TEXT = 4, /*!< Represent a string resource. */
    RESOURCE_FONT = 5, /*!< Represent a font resource. */
};

/*! \enum LANG
    Enum defining every type of lang.
*/
enum LANG
{
    EN, /*!< English. */
    FR, /*!< French. */
    DE, /*!< Deutch. */
    SP, /*!< Spanish. */
};


/*!
    \def _GET_SOUNDBUFFER(key)
    Get the sfml::SoundBuffer from a key.
    \param key String used for ID to search the resource.
    \return First sfml::SoundBuffer * where the id equal to key.
    \throw sfmlbe::ResourceNotFoundException if the resource is not found in any scope.
 */
#define _GET_SOUNDBUFFER(key) ((sfmlbe::ResourceSoundBuffer *)(sfmlbe::ResourceManager::GetInstance()->FindResourceByID(key)))->GetSoundBuffer()

/*!
    \def _GET_SOUNDBUFFER_SCOPE(key, scope)
    Get the sfml::SoundBuffer from a key and a specified scope.
    \param key String used for ID to search the resource.
    \param scope String for the defined scope.
    \return First sfml::SoundBuffer * where the id equal to key.
    \throw sfmlbe::ResourceNotFoundException if the resource is not found in any scope.
    \throw sfmlbe::ScopeNotFoundException if the scope is not found.
 */
#define _GET_SOUNDBUFFER_SCOPE(key, scope) ((sfmlbe::ResourceSoundBuffer *)(sfmlbe::ResourceManager::GetInstance()->FindResourceByID(key, scope)))->GetSoundBuffer()

/*!
    \def _GET_TEXTURE(key)
    Get the sfml::Texture from a key.
    \param key String used for ID to search the resource.
    \return First sfml::Texture * where the id equal to key.
    \throw sfmlbe::ResourceNotFoundException if the resource is not found in any scope.
 */
#define _GET_TEXTURE(key) ((sfmlbe::ResourceTexture *)(sfmlbe::ResourceManager::GetInstance()->FindResourceByID(key)))->GetTexture()

/*!
    \def _GET_TEXTURE_SCOPE(key, scope)
    Get the sfml::Texture from a key and a specified scope.
    \param key String used for ID to search the resource.
    \param scope String for the defined scope.
    \return First sfml::Texture * where the id equal to key.
    \throw sfmlbe::ResourceNotFoundException if the resource is not found in any scope.
    \throw sfmlbe::ScopeNotFoundException if the scope is not found.
 */
#define _GET_TEXTURE_SCOPE(key, scope) ((sfmlbe::ResourceTexture *)(sfmlbe::ResourceManager::GetInstance()->FindResourceByID(key, scope)))->GetTexture()

/*!
    \def _GET_MUSIC(key)
    Get the sfml::Music from a key.
    \param key String used for ID to search the resource.
    \return First sfml::Music * where the id equal to key.
    \throw sfmlbe::ResourceNotFoundException if the resource is not found in any scope.
 */
#define _GET_MUSIC(key) ((sfmlbe::ResourceMusic *)(sfmlbe::ResourceManager::GetInstance()->FindResourceByID(key)))->GetMusic()

/*!
    \def _GET_MUSIC_SCOPE(key, scope)
    Get the sfml::Music from a key and a specified scope.
    \param key String used for ID to search the resource.
    \param scope String for the defined scope.
    \return First sfml::Music * where the id equal to key.
    \throw sfmlbe::ResourceNotFoundException if the resource is not found in any scope.
    \throw sfmlbe::ScopeNotFoundException if the scope is not found.
 */
#define _GET_MUSIC_SCOPE(key, scope) ((sfmlbe::ResourceMusic *)(sfmlbe::ResourceManager::GetInstance()->FindResourceByID(key, scope)))->GetMusic()

/*!
    \def _GET_FONT(key)
    Get the sfml::Font from a key.
    \param key String used for ID to search the resource.
    \return First sfml::Font * where the id equal to key.
    \throw sfmlbe::ResourceNotFoundException if the resource is not found in any scope.
 */
#define _GET_FONT(key) ((sfmlbe::ResourceFont *)(sfmlbe::ResourceManager::GetInstance()->FindResourceByID(key)))->GetFont()

/*!
    \def _GET_FONT_SCOPE(key, scope)
    Get the sfml::Font from a key and a specified scope.
    \param key String used for ID to search the resource.
    \param scope String for the defined scope.
    \return First sfml::Font * where the id equal to key.
    \throw sfmlbe::ResourceNotFoundException if the resource is not found in any scope.
    \throw sfmlbe::ScopeNotFoundException if the scope is not found.
 */
#define _GET_FONT_SCOPE(key, scope) ((sfmlbe::ResourceFont *)(sfmlbe::ResourceManager::GetInstance()->FindResourceByID(key, scope)))->GetFont()

/*!
    \def _GET_TEXT(key, key_text)
    Get the std::String from a key.
    \param key String used for ID to search the resource.
    \param key_text String used for to search the text in the resource.
    \return First std::String * where the id equal to key.
    \throw sfmlbe::ResourceNotFoundException if the resource is not found in any scope.
 */
#define _GET_TEXT(key, key_text) ((sfmlbe::ResourceText *)(sfmlbe::ResourceManager::GetInstance()->FindResourceByID(key)))->GetText(key_text)

/*!
    \def _GET_TEXT_SCOPE(key, scope, key_text)
    Get the std::String from a key and a specified scope.
    \param key String used for ID to search the resource.
    \param scope String for the defined scope.
    \param key_text String used for to search the text in the resource.
    \return First std::String * where the id equal to key.
    \throw sfmlbe::ResourceNotFoundException if the resource is not found in any scope.
    \throw sfmlbe::ScopeNotFoundException if the scope is not found.
 */
#define _GET_TEXT_SCOPE(key, scope, key_text) ((sfmlbe::ResourceText *)(sfmlbe::ResourceManager::GetInstance()->FindResourceByID(key, scope)))->GetText(key_text)

/*!
    Class representing a Singleton pattern for a typename T.
    Used in ResourceManager. Thread safe.
*/
template <typename T> class Singleton
{
	protected:
		//! Constructor.
		Singleton() { }
		//! Destructor.
		~Singleton() { }

	public:
		/*!
		    Static function used to get a reference to the instance of the Singleton templated class (thread safe).
		*/
		static T * GetInstance() 
		{
			if (NULL == _singleton)
			{
				sf::Mutex mutex;
				mutex.lock();
				if (NULL == _singleton)
				{
					_singleton = static_cast<T * >(operator new(sizeof(T)));
					new (_singleton) T;
				}
				mutex.unlock();
			}
			return _singleton;
		}

		/*!
		    Static function used to clear the memory and the reference to the instance of the Singleton templated class.
		*/
		static void Kill()
		{
			if (NULL != _singleton)
			{
				delete _singleton;
				_singleton = NULL;
			}
		}

	private:
		static T *_singleton;
};
template <typename T> T *Singleton<T>::_singleton = NULL;


/*!
    Virtual class representing a Resource. Can be any type of resource listed in RESOURCE_TYPE,
    but every type need to be implemented in a child clas, and the Resource Manager need to be updated.
*/
class Resource
{
    public:
        //! Constructor.
        /*!
            Construct a non loaded null resource.
            \sa Resource(std::string ID, std::string filename) and ~Resource()
        */
        Resource() : m_resourceID("null"), m_filename("null"), m_type(RESOURCE_NULL), m_loaded(false) {}

        //! Constructor.
        /*!
            Construct a non loaded null resource, but with provided parameters.
            \param ID ID of the resource in the scope specified.
            \param filename Relative path of file from where the resource is loaded.
            \sa Resource() and ~Resource()
        */
        Resource(std::string ID, std::string filename) : m_resourceID(ID), m_filename(filename), m_type(RESOURCE_NULL), m_loaded(false) {}

        //! Virtual descructor.
        /*!
            \sa Resource() and Resource(std::string ID, std::string filename)
        */
        virtual ~Resource() {}

        //! Virtual member. Used to load the resource.
        /*!
            \sa Unload()
        */
        virtual void Load() = 0;

        //! Virtual member. Used to unload the resource.
        /*!
            \sa Load()
        */
        virtual void Unload() = 0;

        //! Set the resource ID.
        /*!
            Careful with the use of this function. This function does not unload or test if the resource name is unique in his scope.
            \param ID New ID for the resource.
        */
        void SetResourceID(std::string ID) { m_resourceID = ID; }

        //! Get the resource ID.
        /*!
            \return ID of the resource.
        */
        std::string GetResourceID() const { return m_resourceID; }

        //! Set the resource filename.
        /*!
            Careful with the use of this function. This function does not unload the Resource but set the resource as not loaded.
            \param filename New filename for the resource.
        */
        void SetFilename(std::string filename) { m_loaded = false; m_filename = filename; }

        //! Get the resource filename.
        /*!
            \return Filename of the resource.
        */
        std::string GetFilename() const { return m_filename; }

        //! Set the resource type.
        /*!
            Careful with the use of this function. This function does not change the Resource class, but set as not loaded.
            \param type New type for the resource.
        */
        void SetResourceType(RESOURCE_TYPE type) { m_loaded = false; m_type = type; }

        //! Get the resource type.
        /*!
            \return Resource type of the resource.
        */
        RESOURCE_TYPE GetResourceType() const { return m_type; }

        //! Get if the resource is loaded
        /*!
            \return Is the resource is loaded.
        */
        bool IsLoaded() const { return m_loaded; }

    protected:
        std::string m_resourceID;
        std::string m_filename;
        RESOURCE_TYPE m_type;
        bool m_loaded;
        
    private:
};

/*!
	Exception thrown when a sfmlbe::Ressource is not loaded and should have been loaded.
 */
class ResourceNotLoadException : public std::exception 
{ 
	public: 
	    ResourceNotLoadException(const char * filename) 
	    { 
	        std::ostringstream oss; 
	        oss << "Ressource " << filename << " not loaded."; 
	        this->msg = oss.str(); 
	    } 
	  
	    virtual ~ResourceNotLoadException() throw() 
	    { 
	  
	    } 
	  
	    virtual const char * what() const throw() 
	    { 
	        return this->msg.c_str(); 
	    } 
	  
	private: 
	    std::string msg; 
};

/*!
	Exception thrown when a sfmlbe::Ressource is not found in the resource map.
 */
class ResourceNotFoundException : public std::exception 
{ 
	public: 
	    ResourceNotFoundException(const char * key) 
	    { 
	        std::ostringstream oss; 
	        oss << "Ressource " << key << " not found."; 
	        this->msg = oss.str(); 
	    } 
	  
	    virtual ~ResourceNotFoundException() throw() 
	    { 
	  
	    } 
	  
	    virtual const char * what() const throw() 
	    { 
	        return this->msg.c_str(); 
	    } 
	  
	private: 
	    std::string msg; 
}; 

/*!
	Exception thrown when a scope is not found in the resource map.
 */
class ScopeNotFoundException : public std::exception 
{ 
	public: 
	    ScopeNotFoundException(const char * key) 
	    { 
	        std::ostringstream oss; 
	        oss << "Scope " << key << " not found."; 
	        this->msg = oss.str(); 
	    } 
	  
	    virtual ~ScopeNotFoundException() throw() 
	    { 
	  
	    } 
	  
	    virtual const char * what() const throw() 
	    { 
	        return this->msg.c_str(); 
	    } 
	  
	private: 
	    std::string msg; 
};

/*!
	Class allowing to store a sf::Font using the SFMLBE Resource Manager system.
	Provide an interface to load and unload font easily.
 */
class ResourceFont : public Resource
{
	public:
		//! Constructor.
        /*!
            Construct a non loaded font resource.
            \sa ResourceFont(std::string ID, std::string filename) and ~ResourceFont()
        */
		ResourceFont();

		//! Constructor.
        /*!
            Construct a non loaded font resource, but with provided parameters.
            \param ID ID of the resource in the scope specified.
            \param filename Relative path of file from where the resource is loaded.
            \sa ResourceFont() and ~ResourceFont()
        */
		ResourceFont(std::string ID, std::string filename);

		//! Descructor.
        /*!
        	Free memory used by the sf::Font and this resource.
            \sa ResourceFont() and ResourceFont(std::string ID, std::string filename)
        */
		~ResourceFont();

		//! Load the sf::Font targeted by this resource.
        /*!
        	If success set this resource as loaded.
            \sa Unload() and IsLoaded()
        */
		void Load();

		//! Unload the sf::Font targeted by this resource.
        /*!
        	If success set this resource as unloaded.
            \sa Load() and IsLoaded()
        */
        void Unload();

        //! Get the sf::Font associed to this resource.
        /*!
            \return Reference to the sf::Font or NULL.
        */
		sf::Font * GetFont() {return m_font;}

	private:
		sf::Font * m_font;
};

/*!
	Class allowing to store a sf::Music using the SFMLBE Resource Manager system.
	Provide an interface to load and unload music easily.
 */
class ResourceMusic : public Resource
{
	public:
		//! Constructor.
        /*!
            Construct a non loaded music resource.
            \sa ResourceMusic(std::string ID, std::string filename) and ~ResourceMusic()
        */
		ResourceMusic();

		//! Constructor.
        /*!
            Construct a non loaded music resource, but with provided parameters.
            \param ID ID of the resource in the scope specified.
            \param filename Relative path of file from where the resource is loaded.
            \sa ResourceMusic() and ~ResourceMusic()
        */
		ResourceMusic(std::string ID, std::string filename);

		//! Descructor.
        /*!
        	Free memory used by the sf::Music and this resource.
            \sa ResourceMusic() and ResourceMusic(std::string ID, std::string filename)
        */
		~ResourceMusic();

		//! Load the sf::Music targeted by this resource.
        /*!
        	If success set this resource as loaded.
            \sa Unload() and IsLoaded()
        */
		void Load();

		//! Unload the sf::Music targeted by this resource.
        /*!
        	If success set this resource as unloaded.
            \sa Load() and IsLoaded()
        */
        void Unload();

		//! Get the sf::Music associed to this resource.
        /*!
            \return Reference to the sf::Music or NULL.
        */
		sf::Music * GetMusic() {return m_music;}

	private:
		sf::Music * m_music;
};

/*!
	Class allowing to store a sf::SoundBuffer using the SFMLBE Resource Manager system.
	Provide an interface to load and unload soundbuffer easily.
 */
class ResourceSoundBuffer : public Resource
{
	public:
		//! Constructor.
        /*!
            Construct a non loaded soundbuffer resource.
            \sa ResourceSoundBuffer(std::string ID, std::string filename) and ~ResourceSoundBuffer()
        */
		ResourceSoundBuffer();

		//! Constructor.
        /*!
            Construct a non loaded soundbuffer resource, but with provided parameters.
            \param ID ID of the resource in the scope specified.
            \param filename Relative path of file from where the resource is loaded.
            \sa ResourceSoundBuffer() and ~ResourceSoundBuffer()
        */
		ResourceSoundBuffer(std::string ID, std::string filename);

		//! Descructor.
        /*!
        	Free memory used by the sf::SoundBuffer and this resource.
            \sa ResourceSoundBuffer() and ResourceSoundBuffer(std::string ID, std::string filename)
        */
		~ResourceSoundBuffer();

		//! Load the sf::SoundBuffer targeted by this resource.
        /*!
        	If success set this resource as loaded.
            \sa Unload() and IsLoaded()
        */
		void Load();

		//! Unload the sf::SoundBuffer targeted by this resource.
        /*!
        	If success set this resource as unloaded.
            \sa Load() and IsLoaded()
        */
        void Unload();

        //! Get the sf::SoundBuffer associed to this resource.
        /*!
            \return Reference to the sf::SoundBuffer or NULL.
        */
		sf::SoundBuffer * GetSoundBuffer() {return m_soundBuffer;}
		
	private:
		sf::SoundBuffer * m_soundBuffer;
};

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

/*!
	Class allowing to store a sf::Texture using the SFMLBE Resource Manager system.
	Provide an interface to load and unload texture easily.
 */
class ResourceTexture : public Resource
{
	public:
		//! Constructor.
        /*!
            Construct a non loaded texture resource.
            \sa ResourceTexture(std::string ID, std::string filename) and ~ResourceTexture()
        */
		ResourceTexture();

		//! Constructor.
        /*!
            Construct a non loaded texture resource, but with provided parameters.
            \param ID ID of the resource in the scope specified.
            \param filename Relative path of file from where the resource is loaded.
            \sa ResourceTexture() and ~ResourceTexture()
        */
		ResourceTexture(std::string ID, std::string filename);

		//! Descructor.
        /*!
        	Free memory used by the sf::Texture and this resource.
            \sa ResourceTexture() and ResourceTexture(std::string ID, std::string filename)
        */
		~ResourceTexture();

		//! Load the sf::Texture targeted by this resource.
        /*!
        	If success set this resource as loaded.
            \sa Unload() and IsLoaded()
        */
		void Load();

		//! Unload the sf::Texture targeted by this resource.
        /*!
        	If success set this resource as unloaded.
            \sa Load() and IsLoaded()
        */
        void Unload();

        //! Get the sf::Texture associed to this resource.
        /*!
            \return Reference to the sf::Texture or NULL.
        */
		sf::Texture * GetTexture() {return m_texture;}
        
	private:
		sf::Texture * m_texture;
};

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
        Resource * CreateResource(const tinyxml2::XMLElement * element, const std::string & path);

        //! Load the resources that are not already loaded
        /*!
            \param scope_target Scope where to append the sfmlbe::Resources
        */
        void LoadPendingResources(const std::string & scope_target);

        std::vector<Resource *> m_listOfPendingResources;                           //Resources creates but not stored
        UINT m_resourceCount;                                                       //Total number of resources loaded
        std::map<std::string, std::map<std::string, Resource *> * > m_resources;    //Map of form <scope ID, Resource map>
};

class GameState;

/*!
    \struct GameParameters
    Represent a list of all the caracteristics of the game (and the window).
 */
struct GameParameters
{
    sf::VideoMode windowCaracts;
    bool fullscreen;
    int antialiasingLevel;
    int maxFramerate;
    bool verticalSync;
    LANG lang;
};


/*!
    Class that can handle a game state system.
    Replace the "clear draw display" loop by another loop using a state.
 */
class GameManager
{
    public:

        //! Init the Game Manager.
        /*!
            Init the sf::RenderWindow. Try to use a file next to the exe 'config.ini'.
            If the config file doesn't exist the program create it, but if it's corrupt the programm will not launch.
            \param title Title of the window.
            \sa Cleanup()
        */
        void Init(std::string & title);

        //! Clean the Game Manager.
        /*!
            Pop all states and delete the sf::RenderWindow.
            \sa Init()
        */
        void Cleanup();

        //! Change the current state.
        /*!
            Deletes the last state and replaces it.
            \param state Reference on the state that will be used.
            \sa PushState(GameState * state) and PopState()
        */
        void ChangeState(GameState * state);

        //! Push the current state.
        /*!
            Pauses the current state, pushes the state as parameter on top of the stack and sets as active.
            \param state Reference on the state that will be used.
            \sa ChangeState(GameState * state) and PopState()
        */
        void PushState(GameState * state);

        //! Pop the current state.
        /*!
            Delete the current state from the stack and resume the last one.
            \sa ChangeState(GameState * state) and PushState(GameState * state)
        */
        void PopState();

        //! Call the HandeEvents function on the current state.
        /*!
            \sa Update() and Draw()
        */
        void HandleEvents();

        //! Call the Update function on the current state.
        /*!
            \sa HandleEvents() and Draw()
        */
        void Update();

        //! Call the Draw function on the current state.
        /*!
            \sa HandleEvents() and Update()
        */
        void Draw();

        //! Know if the window is running.
        /*!
            \return True if the window is running.
            \sa Quit()
        */
        bool Running() { return m_running; }

        //! Stop the infinite loop.
        /*! 
            \sa Running()
        */
        void Quit();

        //! Get the reference on the sf::RenderWindow
        /*!
            \return Reference on the sf::RenderWindow.
        */
        sf::RenderWindow * GetWindow() { return m_window; }

        //! Get the size of the window.
        /*!
            \return Size of the window (x, y).
        */
        sf::Vector2u GetSize();

        //! Get the caracteristics of the window and the system.
        /*!
            \return Parameters of the game.
        */
        GameParameters GetParameters() { return m_parameters; }

        //! Set the parameters of the window and system.
        /*!
            This function will only recreate the window and change the .ini, but not reload the lang if changed.
            \param parameters Parameters of the game.
        */
        void SetParameters(GameParameters parameters);

    private:
        bool checkIni();

        std::vector<GameState *> m_states;
        sf::RenderWindow * m_window;
        bool m_running;

        std::string m_title;

        GameParameters m_parameters;
};

/*!
    Virtual class representing a GameState. Need to be inherit to be used with the GameManager.
*/
class GameState
{
    public:
        //! Virtual member. Init the state.
        /*!
            \sa Unload()
        */
        virtual void Init(GameManager * game) = 0;

        //! Virtual member. Cleanup the memory in the state.
        /*!
            \sa Cleanup()
        */
        virtual void Cleanup() = 0;

        //! Virtual member. Pause the state.
        /*!
            \sa Resume()
        */
        virtual void Pause() = 0;

        //! Virtual member. Resume the state.
        /*!
            \sa Pause()
        */
        virtual void Resume() = 0;

        //! Virtual member. Handle the poll event loop.
        /*!
            \param game GameManager that can be used.
            \sa Update(GameManager * game) and Draw(GameManager * game)
        */
        virtual void HandleEvents(GameManager * game) = 0;

        //! Virtual member. Update what to display.
        /*!
            \param game GameManager that can be used.
            \sa HandleEvents(GameManager * game) and Draw(GameManager * game)
        */
        virtual void Update(GameManager * game) = 0;

        //! Virtual member. Draw what to draw.
        /*!
            \param game GameManager that can be used.
            \sa HandleEvents(GameManager * game) and Update(GameManager * game)
        */
        virtual void Draw(GameManager * game) = 0;

        //! Change the actual state.
        /*!
            \param game GameManager that will call the state.
            \param state GameState that will be called.
        */
        void ChangeState(GameManager* game, GameState* state) { game->ChangeState(state); }

    protected:
        //! Constructor.
        /*!
            Construct GameState.
        */
        GameState() { }
};

}
#endif
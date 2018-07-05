#ifndef COMMON_HPP
#define COMMON_HPP

/*!
    \file common.hpp
    \brief Misc of component for SFMLBE
    \author Etienne Andrieu
    \version 1.0
 */

/*! \namespace sfmlbe
    Namespace for this engine.
 */
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

}


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


#endif
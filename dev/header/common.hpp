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

/*!
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
}


#define _GET_TEXTURE(key) ((tr::ResourceTexture *)(tr::ResourceManager::GetInstance()->FindResourceByID(key)))->GetTexture()
#define _GET_TEXTURE_SCOPE(key, scope) ((tr::ResourceTexture *)(tr::ResourceManager::GetInstance()->FindResourceByID(key, scope)))->GetTexture()

#define _GET_SOUNDBUFFER(key) ((tr::ResourceSoundBuffer *)(tr::ResourceManager::GetInstance()->FindResourceByID(key)))->GetSoundBuffer()
#define _GET_SOUNDBUFFER_SCOPE(key, scope) ((tr::ResourceSoundBuffer *)(tr::ResourceManager::GetInstance()->FindResourceByID(key, scope)))->GetSoundBuffer()

#define _GET_MUSIC(key) ((tr::ResourceMusic *)(tr::ResourceManager::GetInstance()->FindResourceByID(key)))->GetMusic()
#define _GET_MUSIC_SCOPE(key, scope) ((tr::ResourceMusic *)(tr::ResourceManager::GetInstance()->FindResourceByID(key, scope)))->GetMusic()

#define _GET_FONT(key) ((tr::ResourceFont *)(tr::ResourceManager::GetInstance()->FindResourceByID(key)))->GetFont()
#define _GET_FONT_SCOPE(key, scope) ((tr::ResourceFont *)(tr::ResourceManager::GetInstance()->FindResourceByID(key, scope)))->GetFont()

#define _GET_TEXT(key, key_text) ((tr::ResourceText *)(tr::ResourceManager::GetInstance()->FindResourceByID(key)))->GetText(key_text)
#define _GET_TEXT_SCOPE(key, scope, key_text) ((tr::ResourceText *)(tr::ResourceManager::GetInstance()->FindResourceByID(key, scope)))->GetText(key_text)

}

#endif
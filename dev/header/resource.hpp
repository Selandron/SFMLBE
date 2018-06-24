#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>

namespace sfmlbe
{

/*!
    Enum defining every type of resource possible.
*/
typedef enum
{
    RESOURCE_NULL = 0, /*!< Represent a not valid resource. */
    RESOURCE_GRAPHIC = 1, /*!< Represent a texture resource. */
    RESOURCE_SOUNDBUFFER = 2, /*!< Represent a soundbuffer resource. */
    RESOURCE_MUSIC = 3, /*!< Represent a music resource. */
    RESOURCE_TEXT = 4, /*!< Represent a string resource. */
    RESOURCE_FONT = 5, /*!< Represent a font resource. */
}RESOURCE_TYPE;

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

}
#endif
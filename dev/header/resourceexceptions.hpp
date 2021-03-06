#ifndef RESOURCEEXCEPTIONS_HPP
#define RESOURCEEXCEPTIONS_HPP

#include <iostream> 
#include <sstream> 
#include <exception> 

/*!
    \file resourceexceptions.hpp
    \brief All the exceptions used in the Resource system.
    \author Etienne Andrieu
    \version 1.0
 */

namespace sfmlbe
{
  
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

}
#endif
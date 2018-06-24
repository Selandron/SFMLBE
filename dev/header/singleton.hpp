#ifndef SINGLETON_HPP
#define SINGLETON_HPP

/*
	Template Singleton thread-safe based on this tutorial : https://come-david.developpez.com/tutoriels/dps/?page=Singleton

	Author : Etienne Andrieu
*/

#include <SFML/System.hpp>

namespace sfmlbe
{

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

}

#endif
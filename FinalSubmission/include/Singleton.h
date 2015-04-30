/// @file Singleton.h
/// @brief Makes sure that no object is instanciated twice.

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

/// @class Singleton
/// @brief Makes sure that no object is instanciated twice.
template <class T>
class Singleton
{
public:
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief If the instance is null it creates one, otherwise just returns the current one.
  //--------------------------------------------------------------------------------------------------------------------
  static T* Instance()
  {
    if(!m_Instance)
    {
      m_Instance = new T;
    }
    return m_Instance;
  }
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Destroys the instance thus freeing memory from the heap.
  //--------------------------------------------------------------------------------------------------------------------
  static void destroyInstance()
  {
    delete m_Instance;
  }

private:
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief The instance of an object as an address.
  //--------------------------------------------------------------------------------------------------------------------
  static T* m_Instance;
};

// Set it initially to NULL
template<class T>
T* Singleton<T>::m_Instance = NULL;

#endif // Singleton.h

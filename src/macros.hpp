/**
 * @file macros.hpp 
 * @author xmdf
 * @date 30 June 2022
 * @brief Useful macros
 */

#ifndef __DPS_MACROS_HPP__
#define __DPS_MACROS_HPP__


// TODO look into this
#if __cplusplus >= 201103L
#define DPS_CPP11
#endif


#if !defined DPS_DEFAULT
#if defined DPS_CPP11
#define DPS_DEFAULT = default;
#else
#define DPS_DEFAULT                                                            \
    {                                                                          \
    }
#endif
#endif


#if !defined DPS_NON_COPYABLE_NOR_MOVABLE
#if defined DPS_CPP11
#define DPS_NON_COPYABLE_NOR_MOVABLE(classname_)                               \
  public:                                                                      \
    classname_ (const classname_&) = delete;                                   \
    classname_ &operator= (const classname_&) = delete;                        \
    classname_ (classname_&&) = delete;                                        \
    classname_ &operator= (classname_&&) = delete;
#else
#define DPS_NON_COPYABLE_NOR_MOVABLE(classname_)                               \
   private:                                                                    \
     classname_ (const classname_&);                                           \
     classname_ &operator= (classname_&);
#endif
#endif


#endif // __DPS_MACROS_HPP__

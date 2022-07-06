/**
 * @file macros.hpp 
 * @author xmdf
 * @date 30 June 2022
 * @brief Useful macros
 */

#ifndef __DPS_MACROS_HPP__
#define __DPS_MACROS_HPP__


#if !defined DPS_NON_COPYABLE_NOR_MOVABLE
#define DPS_NON_COPYABLE_NOR_MOVABLE(classname_)                               \
  public:                                                                      \
    classname_ (const classname_&) = delete;                                   \
    classname_ &operator= (const classname_&) = delete;                        \
    classname_ (classname_&&) = delete;                                        \
    classname_ &operator= (classname_&&) = delete;
#endif


#endif // __DPS_MACROS_HPP__

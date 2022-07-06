/**
 * @file utils.cpp 
 * @author xmdf
 * @date 30 June 2022
 * @brief
 */

#include "utils.hpp"

#include <cerrno>
#include <iostream>

namespace dps::utils {


    void print_errno() {
        std::cout << ::strerror(errno) << "(" << errno << ")" << std::endl;
    }


} // end namespace dps::utils

/**
 * @file utils.hpp 
 * @author xmdf
 * @date 30 June 2022
 * @brief
 */

#ifndef __DPS_UTILS_HPP__
#define __DPS_UTILS_HPP__

#include <chrono>


namespace dps::utils {

    /// prints errno string and number
    void print_errno();


    template <typename Rep_, typename Period_>
    bool timeout_has_occurred(
        const std::chrono::time_point<std::chrono::steady_clock> & start,
        const std::chrono::duration<Rep_, Period_> timeout)
    {
        return (std::chrono::steady_clock::now() - start) > timeout;
    }


} // end namespace dps::utils


#endif // __DPS_UTILS_HPP__

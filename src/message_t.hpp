/**
 * @file message_t.hpp 
 * @author xmdf
 * @date 25 July 2022
 * @brief
 */

#ifndef __DPS_MESSAGE_T_HPP__
#define __DPS_MESSAGE_T_HPP__

#include <cstdlib>


namespace dps {

    using byte_t = uint8_t;

    class message_t
    {
    public:
        message_t()
        : data_{nullptr}
        , size_{0}
        {
        }

        message_t(
            const void *data,
            size_t size)
        : data{memcpy(data, this->data_)}

    private:
        std::shared_ptr<std::vector data_;
        size_t size_;
    };

} // end namespace dps



#endif // __DPS_MESSAGE_T_HPP__

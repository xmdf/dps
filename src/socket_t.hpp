/**
 * @file socket_t.hpp 
 * @author xmdf
 * @date 30 June 2022
 * @brief
 */

#ifndef __DPS_SOCKET_T_HPP__
#define __DPS_SOCKET_T_HPP__

#include <netinet/in.h>
#include <sys/poll.h>

#include <string>

#include "macros.hpp"


namespace dps {

    /// Just being cheeky here
    using sock_fd_t = int;


    /**
     * Return status for many socket functions
     */
    enum class Status {
        SUCCESS,
        FAIL,
        TIMEOUT
    };


    /**
     * @brief Objectification of low-level BSD socket
     */
    class socket_t
    {
    public:
        socket_t();

        in_port_t port() const;

        std::string ip_address() const;

        std::string socket_address() const;

        Status connect(
            const std::string &ip_address,
            in_port_t port);

        Status bind(
            const std::string &ip_address,
            in_port_t port);

        Status listen(
            int connection_limit = 5) const;

        Status accept(
            std::shared_ptr<socket_t> &client_socket,
            const std::chrono::milliseconds &timeout =
                std::chrono::milliseconds{-1});

        Status recv(
            void *data,
            size_t sz,
            const std::chrono::milliseconds &timeout =
                std::chrono::milliseconds{-1});

        Status send(
            void const *data,
            size_t sz,
            const std::chrono::milliseconds &timeout =
            std::chrono::milliseconds{-1}) const;

        Status close();

        virtual ~socket_t();

        DPS_NON_COPYABLE_NOR_MOVABLE(socket_t)

    private:
        explicit socket_t(
            bool init);

        void socket_init();

        Status create_address(
            const std::string &ip_address,
            in_port_t port);

        Status poll(
            const std::chrono::milliseconds &timeout);

    private:
        sock_fd_t socket_fd_;
        std::unique_ptr<struct sockaddr_in> sockaddr_in_;
        std::unique_ptr<struct pollfd> poller_;
    };

} // end namespace dps



#endif // __DPS_SOCKET_T_HPP__

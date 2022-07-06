/**
 * @file socket_t.cpp 
 * @author xmdf
 * @date 30 June 2022
 * @brief
 */

#include "socket_t.hpp"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <exception>
#include <iostream>
#include <sstream>
#include <thread>

#include "utils.hpp"


namespace dps {

    //==========================================================================
    // dps::socket_t
    //==========================================================================
    //------------------------------------------------------
    // socket_t::socket_t()
    //------------------------------------------------------
    socket_t::socket_t()
    : socket_fd_{-1}
    , sockaddr_in_{std::make_unique<struct sockaddr_in>()}
    , poller_{std::make_unique<struct pollfd>()}
    {
        this->poller_->events = POLLIN;
        this->socket_init();
    }

    //------------------------------------------------------
    // socket_t::socket_t(bool)
    //------------------------------------------------------
    socket_t::socket_t(bool init)
    : socket_fd_{-1}
    , sockaddr_in_{std::make_unique<struct sockaddr_in>()}
    , poller_{std::make_unique<struct pollfd>()}
    {
        this->poller_->events = POLLIN;
        if (init) {
            this->socket_init();
        }
    }

    //------------------------------------------------------
    // socket_t::~socket_t()
    //------------------------------------------------------
    socket_t::~socket_t()
    {
        this->close();
    }
    
    //------------------------------------------------------
    // socket_t::init()
    //------------------------------------------------------
    void socket_t::socket_init()
    {
        // create actual socket
        if ((this->socket_fd_ =
                 socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0)
        {
            utils::print_errno();
            throw std::runtime_error("Error creating socket.");
        }

        // set socket options
        const int options = 1;
        if (setsockopt(this->socket_fd_, SOL_SOCKET, SO_REUSEADDR,
                       &options, sizeof(options)) < 0)
        {
            utils::print_errno();
            throw std::runtime_error("Error setting options on socket.");
        }

        // assign poller file-descriptor and address family
        this->poller_->fd = this->socket_fd_;
        this->sockaddr_in_->sin_family = AF_INET;
    }

    //------------------------------------------------------
    // socket_t::port()
    //------------------------------------------------------
    in_port_t socket_t::port() const
    {
        struct sockaddr_in sin{};
        socklen_t len = sizeof(sin);
        if (getsockname(
                this->socket_fd_,
                reinterpret_cast<struct sockaddr*>(&sin), &len) < 0)
        {
            return 0;
        }
            
        return ntohs(sin.sin_port);
    }

    //------------------------------------------------------
    // socket_t::ip_address()
    //------------------------------------------------------
    std::string socket_t::ip_address() const
    {
        char buf[64];
        return std::string{
            inet_ntop(AF_INET, this->sockaddr_in_.get(), buf, sizeof(buf))};
    }

    //------------------------------------------------------
    // socket_t::socket_address()
    //------------------------------------------------------
    std::string socket_t::socket_address() const
    {
        return std::string{
            this->ip_address() + ":" + std::to_string(this->port())};
    }

    //------------------------------------------------------
    // socket_t::create_address()
    //------------------------------------------------------
    Status socket_t::create_address(
        const std::string &ip_address,
        in_port_t port)
    {
        // reserved ports for the OS
        if ((port > 0) && (port < 1023)) {
            std::stringstream ss;
            ss << "Invalid port " << port;
            throw std::runtime_error(ss.str());
        }

        // assign port
        this->sockaddr_in_->sin_port = htons(port);

        // assign ip address
        const auto rc =
            inet_pton(AF_INET, ip_address.c_str(), this->sockaddr_in_.get());
        if (rc <= 0) {
            if (rc == 0) {
                std::stringstream ss;
                ss << "Invalid network (ip) address "
                   << "\"" << ip_address << "\"";
                throw std::runtime_error(ss.str());
            }
            else {
                utils::print_errno();
            }

            return Status::FAIL;
        }

        return Status::SUCCESS;
    }

    //------------------------------------------------------
    // socket_t::connect()
    //------------------------------------------------------
    Status socket_t::connect(
        const std::string &ip_address,
        in_port_t port)
    {
        // assign address and port
        if (this->create_address(ip_address, port) == Status::FAIL) {

            return Status::FAIL;
        }
        // bind to address
        if (::connect(
                this->socket_fd_,
                reinterpret_cast<struct sockaddr*>(this->sockaddr_in_.get()),
                sizeof(*this->sockaddr_in_)) < 0)
        {
            utils::print_errno();

            return Status::FAIL;
        }
        std::cout << "Connected to " << this->socket_address() << std::endl;

        return Status::SUCCESS;
    }

    //------------------------------------------------------
    // socket_t::bind()
    //------------------------------------------------------
    Status socket_t::bind(
        const std::string &ip_address,
        in_port_t port)
    {
        // assign address and port
        if (this->create_address(ip_address, port) == Status::FAIL) {

            return Status::FAIL;
        }

        // bind to address
        if (::bind(
            this->socket_fd_,
            reinterpret_cast<struct sockaddr*>(this->sockaddr_in_.get()),
            sizeof(*this->sockaddr_in_)) < 0)
        {
            utils::print_errno();

            return Status::FAIL;
        }
        std::cout << "Bound to " << this->socket_address() << std::endl;

        return Status::SUCCESS;
    }

    //------------------------------------------------------
    // socket_t::listen()
    //------------------------------------------------------
    Status socket_t::listen(
        int connection_limit) const
    {
        if (::listen(this->socket_fd_, connection_limit) < 0) {
            utils::print_errno();

            return Status::FAIL;
        }

        return Status::SUCCESS;
    }

    Status socket_t::accept(
        std::shared_ptr<socket_t> &client_socket,
        const std::chrono::milliseconds &timeout)
    {
        // make sure socket is un-initialized
        if (client_socket->socket_fd_ != -1) {

            return Status::FAIL;
        }
        // wait for timeout or event (connection)
        const auto ps = this->poll(timeout);
        // poll failed
        if (ps == Status::FAIL) {

            return Status::FAIL;
        }
        // timeout reached
        if (ps == Status::TIMEOUT) {

            return Status::TIMEOUT;
        }

        // attempt accept()
        socklen_t len = sizeof(*client_socket->sockaddr_in_);
        client_socket->socket_fd_ =
            ::accept(this->socket_fd_, reinterpret_cast<struct sockaddr*>(
                         client_socket->sockaddr_in_.get()), &len);
        if (client_socket->socket_fd_ == -1) {

            return Status::FAIL;
        }
        client_socket->poller_->fd = client_socket->socket_fd_;

        return Status::SUCCESS;
    }

    //------------------------------------------------------
    // socket_t::recv()
    //------------------------------------------------------
    Status socket_t::recv(
        void *data,
        size_t sz,
        const std::chrono::milliseconds &timeout)
    {
        // always succeed when expecting 0 bytes
        if (sz == 0) {

            return Status::SUCCESS;
        }
        // initialize start time and amount received
        const auto start = std::chrono::steady_clock::now();
        ssize_t recv_sz_total = 0;

        // poll and wait on event (recv) or timeout
        const auto ps = this->poll(timeout);
        // poll failed
        if (ps == Status::FAIL) {

            return Status::FAIL;
        }
        // timeout reached
        if (ps == Status::TIMEOUT) {
            return Status::TIMEOUT;
        }

        // attempt to receive until we have received
        // the total expected bytes (sz)
        auto ptr = reinterpret_cast<char*>(data);
        while (true) {
            const auto recv_sz = ::recv(this->socket_fd_, ptr, sz, 0);
            if (recv_sz == 0) {
                // TODO
                std::this_thread::sleep_for(std::chrono::milliseconds{10});
                continue;
            }
            // bad recv()
            if (recv_sz == -1) {
                utils::print_errno();

                return Status::FAIL;
            }

            // increment our total received and ptr by amount received
            ptr += recv_sz;
            recv_sz_total += recv_sz;

            // if total amount received is expected, break
            if (recv_sz_total >= sz) {
                break;
            }
            // check for timeout
            if (utils::timeout_has_occurred(start, timeout)) {
                // Began to receive data but didn't receive all results in fail
                if (recv_sz_total < sz) {
                    // TODO logging

                    return Status::FAIL;
                }

                return Status::TIMEOUT;
            }
        }

        return Status::SUCCESS;
    }

    //------------------------------------------------------
    // socket_t::send()
    //------------------------------------------------------
    Status socket_t::send(
        const void *data,
        size_t sz,
        const std::chrono::milliseconds &timeout) const
    {
        // don't attempt anything with sz == 0
        if (sz == 0) {

            return Status::SUCCESS;
        }

        // initialize start time and total amount sent
        const auto start = std::chrono::steady_clock::now();
        ssize_t send_sz_total = 0;

        // attempt to send data until total expected has been sent or timeout
        auto ptr = reinterpret_cast<const char*>(data);
        while (true) {
            const auto send_sz =
                ::send(this->socket_fd_, data, sz, MSG_NOSIGNAL);
            // bad send()
            if (send_sz == -1) {
                utils::print_errno();

                return Status::FAIL;
            }
            // increment amount sent and ptr
            send_sz_total += send_sz;
            ptr += send_sz;

            // check if all data has been sent
            if (send_sz_total >= send_sz) {
                break;
            }
            // check for timeout
            if (utils::timeout_has_occurred(start, timeout)) {
                return Status::TIMEOUT;
            }
        }

        return Status::SUCCESS;
    }

    //------------------------------------------------------
    // socket_t::poll()
    //------------------------------------------------------
    Status socket_t::poll(
        const std::chrono::milliseconds &timeout)
    {
        const auto rc =
            ::poll(this->poller_.get(), 1, static_cast<int>(timeout.count()));
        if (rc < 0) {
            utils::print_errno();

            return Status::FAIL;
        }
        if (rc == 0) {

            return Status::TIMEOUT;
        }

        return Status::SUCCESS;
    }

    //------------------------------------------------------
    // socket_t::close()
    //------------------------------------------------------
    Status socket_t::close()
    {
        if (this->socket_fd_ == -1) {

            return Status::SUCCESS;
        }
        if (::close(this->socket_fd_) == -1) {
            utils::print_errno();

            return Status::FAIL;
        }
        this->socket_fd_ = -1;

        return Status::SUCCESS;
    }
    
} // end namespace dps

/**
 * @file thread_t.cpp 
 * @author xmdf
 * @date 12 July 2022
 * @brief
 */

#include "loop_thread_t.hpp"

#include <exception>
#include <iostream>


namespace dps {

    //------------------------------------------------------
    // thread_t::thread_t()
    //------------------------------------------------------
    loop_thread_t::loop_thread_t(
        const loop_thread_t::function_t &fn)
    : fn_{fn}
    , thread_{nullptr}
    , should_run_{false}
    , has_started_{false}
    , is_complete_{false}
    {
    }

    //------------------------------------------------------
    // thread_t::~thread_t()
    //------------------------------------------------------
    loop_thread_t::~loop_thread_t()
    {
        this->stop();
    }

    //------------------------------------------------------
    // thread_t::has_started()
    //------------------------------------------------------
    bool loop_thread_t::has_started() const
    {
        return this->has_started_.load();
    }

    //------------------------------------------------------
    // thread_t::is_complete()
    //------------------------------------------------------
    bool loop_thread_t::is_complete() const
    {
        return this->is_complete_.load();
    }

    //------------------------------------------------------
    // thread_t::start()
    //------------------------------------------------------
    void loop_thread_t::start()
    {
        // tell thread it should start
        this->should_run_.store(true);
        if (this->thread_ == nullptr) {
            this->thread_ = std::make_unique<std::thread>(
                [this](){ this->thread_function(); });
        }
    }

    //------------------------------------------------------
    // thread_t::request_stop()
    //------------------------------------------------------
    void loop_thread_t::request_stop()
    {
        this->should_run_.store(false);
    }

    //------------------------------------------------------
    // thread_t::stop()
    //------------------------------------------------------
    void loop_thread_t::stop()
    {
        this->request_stop();
        if (this->thread_ != nullptr) {
            this->thread_->join();
            this->thread_.reset(nullptr);
        }
    }

    //------------------------------------------------------
    // thread_t::thread_function()
    //------------------------------------------------------
    void loop_thread_t::thread_function()
    {
        try {
            this->has_started_.store(true);
            this->fn_(this->should_run_);
            this->is_complete_.store(true);
        }
        catch(...) {
            std::cerr << "Exception in thread: "
                      << this->thread_->get_id() << std::endl;
            std::rethrow_exception(std::current_exception());
        }
    }


} // end namespace dps
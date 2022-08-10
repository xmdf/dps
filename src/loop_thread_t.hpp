/**
 * @file thread_t.hpp 
 * @author xmdf
 * @date 12 July 2022
 * @brief
 */

#ifndef __DPS_THREAD_T_HPP__
#define __DPS_THREAD_T_HPP__


#include <atomic>
#include <functional>
#include <memory>
#include <thread>

#include "macros.hpp"


namespace dps {

    /**
     *
     */
    class loop_thread_t
    {
    public:
        typedef std::function<void(std::atomic<bool>&)> function_t;

    public:
        /**
         *
         */
        explicit loop_thread_t(
             const function_t &fn);

        /**
         *
         * @return
         */
        bool has_started() const;

        /**
         *
         * @return
         */
        bool is_complete() const;

        /**
         * Runs thread_function() on a thread. If thread has already been
         * started without stop() being called, nothing happens.
         */
        void start();

        /**
         * Requests that the thread complete its processing
         * NOTE: This does *not* call join()
         */
        void request_stop();

        /**
         * Actually stop the thread (this is where join() is called)
         */
        void stop();

        virtual ~loop_thread_t();
        DPS_NON_COPYABLE_NOR_MOVABLE(loop_thread_t)

    private:
        void thread_function();

    private:
        const function_t fn_;
        std::unique_ptr<std::thread> thread_;
        std::atomic<bool> should_run_;
        std::atomic<bool> has_started_;
        std::atomic<bool> is_complete_;
    };


} // end namespace dps


#endif // __DPS_THREAD_T_HPP__

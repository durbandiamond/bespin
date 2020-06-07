/*
 * Copyright (c) 2020 Durban & Diamond, LLC.
 *
 * This file is part of bespin.
 *
 * bespin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <cassert>

#include <bespin/logger.hpp>
#include <bespin/stack.hpp>
#include <bespin/stack_impl.hpp>

using namespace bespin;

stack_impl::stack_impl(stack * owner)
    : stack_(owner)
#if (defined USE_ASIO && USE_ASIO)
    , timer_tick_1000ms_(io_context_)
#endif // USE_ASIO
{
    // ...
}

void stack_impl::start()
{
    LOG_DEBUG("Starting...");
    
    assert(stack_ != 0);
    
#if (defined USE_ASIO && USE_ASIO)
    /**
     * Allocate the  asio::io_context std::thread.
     */
    thread_io_context_ = std::thread([this]
    {
        io_context_.run();
    });
    
    /**
     * Starts the tick timer.
     */
    timer_tick_1000ms_.expires_from_now(std::chrono::milliseconds(1000));
    timer_tick_1000ms_.async_wait([this](std::error_code ec)
    {
        if (ec)
        {
            // ...
        }
        else
        {
            on_tick_1000ms();
        }
    });
#endif // USE_ASIO

    // ...
    
    LOG_DEBUG("Started...");
}

void stack_impl::stop()
{
    LOG_DEBUG("Stopping...");
    
    // ...
#if (defined USE_ASIO && USE_ASIO)
    /**
     * Cancel the timer_tick_1000ms_.
     */
    timer_tick_1000ms_.cancel();
    /**
     * Join the  asio::io_context std::thread.
     */
    thread_io_context_.join();
#endif // USE_ASIO
    
    LOG_DEBUG("Stopped...");
}
#if (defined USE_ASIO && USE_ASIO)
void stack_impl::on_tick_1000ms()
{
    LOG_DEBUG("Tick...");
    
    // ...
    
    /**
     * Starts the tick timer.
     */
    timer_tick_1000ms_.expires_from_now(std::chrono::milliseconds(1000));
    timer_tick_1000ms_.async_wait([this](std::error_code ec)
    {
        if (ec)
        {
            // ...
        }
        else
        {
            on_tick_1000ms();
        }
    });
}
#endif // USE_ASIO

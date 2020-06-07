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

#ifndef stack_impl_hpp
#define stack_impl_hpp

#include <stdio.h>

#include <thread>

/**
 * Enables ASIO support.
 */
#define USE_ASIO 0

#if (defined USE_ASIO && USE_ASIO)
#include <asio.hpp>
#endif // USE_ASIO

namespace bespin {
    
    class stack;
    
    /**
     * Implements the stack implementation.
     */
    class stack_impl
    {
        public:
        
            /**
             * Constructor
             * @param owner The owning stack.
             */
            explicit stack_impl(stack * owner);
            
            /**
             * Starts
             */
            void start();
            
            /**
             * Stops
             */
            void stop();
            
        private:
        
#if (defined USE_ASIO && USE_ASIO)
            /**
             * The timer_tick_1000ms_ handler.
             */
            void on_tick_1000ms();
#endif // USE_ASIO

        protected:
        
            /**
             * The owning stack.
             */
            stack * stack_ = 0;
            
#if (defined USE_ASIO && USE_ASIO)
            /**
             * The asio::io_context std::thread.
             */
            std::thread thread_io_context_;
            
            /**
             * The asio::io_context.
             */
            asio::io_context io_context_;
            
            /**
             * The 1000 millisecond tick timer.
             */
            asio::basic_waitable_timer<
                std::chrono::steady_clock
            > timer_tick_1000ms_;
#endif // USE_ASIO
    };
    
} // namespace bespin

#endif /* stack_impl_hpp */

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

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#include <asio.hpp>

#include <bespin/logger.hpp>
#include <bespin/stack.hpp>

int main(int argc, const char * argv[])
{
    LOG_DEBUG("Begin main...");
    
    asio::io_context io_context;

    asio::signal_set signals(io_context, SIGINT, SIGTERM);
    
    signals.async_wait([&](auto, auto)
    {
        io_context.stop();

    });
    
    bespin::stack bespin_stack;
    
    bespin_stack.start();
    
    io_context.run();
    
    bespin_stack.stop();
    
    LOG_DEBUG("End main...");
     
    return 0;
}

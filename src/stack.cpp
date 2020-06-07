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
#include <stdexcept>

#include <bespin/logger.hpp>
#include <bespin/stack.hpp>
#include <bespin/stack_impl.hpp>

using namespace bespin;

void stack::start()
{
    LOG_DEBUG("Starting...");
    
    assert(stack_impl_ == 0);
    
    stack_impl_ = new stack_impl(this);
    
    assert(stack_impl_ != 0);
    
    if (stack_impl_ != 0)
    {
        stack_impl_->start();
        
        LOG_DEBUG("Started...");
    }
    else
    {
        throw std::runtime_error(
            "stack::start failed to allocate stack_impl"
        );
    }
}

void stack::stop()
{
    LOG_DEBUG("Stopping...");
    
    assert(stack_impl_ != 0);
    
    stack_impl_->stop();
    
    delete stack_impl_;
    
    stack_impl_ = 0;
    
    LOG_DEBUG("Stopped...");
}
            

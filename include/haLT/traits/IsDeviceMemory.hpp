/* This file is part of HaLT.
 *
 * HaLT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * HaLT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with HaLT.  If not, see <www.gnu.org/licenses/>.
 */
 
#pragma once

namespace haLT {
namespace traits{

        /**
         * Returns whether the given data container is already on the device or not
         * A true_type implies that the underlying memory is on the device and therefore a reference is a device pointer
         */
        template< typename T >
        struct IsDeviceMemory: std::false_type{};

}  // namespace traits
}  // namespace haLT

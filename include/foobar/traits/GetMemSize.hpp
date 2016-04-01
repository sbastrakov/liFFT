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

namespace foobar {
namespace traits {

    /**
     * Returns the size of the allocated memory in bytes
     */
    template<class T>
    struct GetMemSize
    {
        size_t operator()(const T& data) const
        {
            return data.getMemSize();
        }
    };

    template<class T>
    struct GetMemSize<const T>: GetMemSize<T>{};

    template<class T>
    struct GetMemSize<T&>: GetMemSize<T>{};

    template<class T>
    size_t
    getMemSize(const T& data)
    {
        return GetMemSize<T>()(data);
    }

}  // namespace traits
}  // namespace foobar

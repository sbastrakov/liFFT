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

#include "foobar/libraries/cuFFT/traits/LibTypes.hpp"
#include "foobar/policies/GetNumElements.hpp"

namespace foobar {
namespace libraries {
namespace cuFFT {
namespace policies {

    /**
     * Getting memory size for inplace transforms is a bit tricky. Therefore use this trait
     */
    template< typename T_Precision, bool T_isComplexIn, bool T_isComplexOut, unsigned T_numDims >
    struct GetInplaceMemSize
    {
        using Precision = T_Precision;
        static constexpr bool isComplexIn = T_isComplexIn;
        static constexpr bool isComplexOut = T_isComplexOut;
        static constexpr unsigned numDims = T_numDims;

        using LibTypes = traits::LibTypes< Precision, isComplexIn, isComplexOut >;
        using LibInType = typename LibTypes::InType;
        using LibOutType = typename LibTypes::OutType;

        template< class T_Extents >
        static size_t
        get(const T_Extents& fullExtents)
        {
            // ATTENTION: Complex values take up more space then real values. Make sure we have enough!
            // Get the extents from the complex values (also for C2R/R2C)
            auto extents(fullExtents);
            if(!isComplexIn || !isComplexOut)
                extents[numDims - 1] = extents[numDims - 1] / 2 + 1;
            // Get number of complex elements
            unsigned numElements = foobar::policies::getNumElementsFromExtents(extents);
            return numElements * (isComplexIn ? sizeof(LibInType) : sizeof(LibOutType));
        }
    };

}  // namespace policies
}  // namespace cuFFT
}  // namespace libraries
}  // namespace foobar

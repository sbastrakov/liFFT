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

#include <cufft.h>

namespace foobar {
namespace libraries {
namespace cuFFT {
namespace traits{

        /**
         * Defines the sign for the given FFT type (forward/backward)
         */
        template< bool T_isFwd=true >
        struct Sign: std::integral_constant<int, CUFFT_FORWARD>{};

        template<>
        struct Sign<false>: std::integral_constant<int, CUFFT_INVERSE>{};

}  // namespace traits
}  // namespace cuFFT
}  // namespace libraries
}  // namespace foobar

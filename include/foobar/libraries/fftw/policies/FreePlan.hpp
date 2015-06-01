#pragma once

#include <fftw3.h>
#include "foobar/libraries/fftw/traits/Types.hpp"

namespace foobar {
namespace libraries {
namespace fftw {
namespace policies{

    /**
     * Frees a given plan
     */
    template< typename T_Precision >
    struct FreePlan;

    template
    struct FreePlan<float>
    {
        using PlanType = typename traits::Types<float>::PlanType;

        void
        operator()(PlanType& plan)
        {
            fftwf_destroy_plan(plan);
        }
    };

    template
    struct FreePlan<double>
    {
        using PlanType = typename traits::Types<double>::PlanType;

        void
        operator()(PlanType& plan)
        {
            fftw_destroy_plan(plan);
        }
    };

} // namespace traits
}  // namespace fftw
}  // namespace libraries
}  // namespace foobar

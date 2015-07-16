#pragma once

#include "foobar/types/Vec.hpp"
#include "foobar/traits/DefaultAccessor.hpp"
#include "foobar/traits/NumDims.hpp"
#include "foobar/accessors/ArrayAccessor.hpp"
#include "foobar/policies/GetExtents.hpp"
#include "foobar/types/Range.hpp"

namespace foobar {
namespace types {

    /**
     * Provides a view on a container
     * Outside users will see it like it has a specific extent which is only a part of the real extents
     * The view is specified by an offset (in each dimension) and the extents (in each dimension)
     */
    template<
        class T_Base,
        class T_BaseAccessor = traits::DefaultAccessor_t<T_Base>
    >
    class View
    {
        using Base = T_Base;
        using BaseAccessor = T_BaseAccessor;

    public:
        static constexpr unsigned numDims = traits::NumDims<Base>::value;
        using Extents = Vec<numDims>;
        using Accessor = accessors::ArrayAccessor<true>;

    private:
        Base& base_;
        const BaseAccessor& acc_;
        Extents offsets_, extents;
        friend class policies::GetExtents<View>;

    public:

        /**
         * Creates a view with offsets and extents
         * Validation on those is performed at runtime
         *
         * @param base Base container
         * @param offsets Offsets for each dimension
         * @param extents New extents
         * @param acc Accessor to access the base class
         */
        View(Base& base, const Extents& offsets, const Extents& extents, const BaseAccessor& acc = BaseAccessor()):
            base_(base), acc_(acc), offsets_(offsets), extents(extents)
        {
            policies::GetExtents<Base> bExtents(base_);
            for(unsigned i=0; i<numDims; ++i)
            {
                if(extents[i] > bExtents[i])
                    throw std::runtime_error("Invalid extents");
                if(offsets[i] + extents[i] > bExtents[i])
                    throw std::runtime_error("Invalid offset or extent");
            }
        }

        template<typename T_Idx>
        std::result_of_t< BaseAccessor(const T_Idx&, Base&) >
        operator()(T_Idx idx)
        {
            for(unsigned i=0; i<numDims; ++i)
                idx[i]+=offsets_[i];
            return acc_(idx, base_);
        }

        template<typename T_Idx>
        std::result_of_t< BaseAccessor(const T_Idx&, const Base&) >
        operator()(T_Idx idx) const
        {
            for(unsigned i=0; i<numDims; ++i)
                idx[i]+=offsets_[i];
            const Base& cBase = const_cast<const Base&>(base_);
            return acc_(idx, cBase);
        }
    };

    template<
            class T_Base,
            class T_BaseAccessor = traits::DefaultAccessor_t<T_Base>,
            class T_Range
        >
    View< T_Base, T_BaseAccessor >
    makeView(T_Base& base, const T_Range& range, const T_BaseAccessor& acc = T_BaseAccessor())
    {
        using Base = std::remove_cv_t<T_Base>;
        return View< T_Base, T_BaseAccessor >(
                base,
                GetRangeOffset<T_Range, Base>::get(range),
                GetRangeExtents<T_Range, Base>::get(range, base),
                acc);
    }
}  // namespace types
}  // namespace foobar
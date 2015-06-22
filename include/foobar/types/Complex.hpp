#pragma once

#include "foobar/types/Real.hpp"

namespace foobar {
namespace types {

    template< typename T=double, bool T_isConst = false >
    struct ComplexRef;

    /**
     * Type used to store complex values (real and imaginary part)
     * Uses the template parameter to choose the memory type (precision)
     */
    template< typename T=double >
    struct Complex
    {
        using type = T;
        static constexpr bool isComplex = true;
        Real<T> real, imag;

        Complex(){}
        template< typename U, typename = std::enable_if_t< std::is_integral<U>::value > >
        Complex(U real): real(std::forward<U>(real)), imag(0){}
        template< typename U, typename V >
        Complex(U&& real, V&& imag): real(std::forward<U>(real)), imag(std::forward<V>(imag)){}
        template< typename U, bool T_isConst >
        Complex(const ComplexRef<U, T_isConst>& ref): real(ref.real), imag(ref.imag){}

        template< typename U >
        Complex&
        operator=(U&& real)
        {
            real = std::forward<U>(real);
            imag = 0;
            return *this;
        }
    };

    /**
     * Generic reference to a complex value
     * Can be used with either AoS or SoA
     *
     * \tparam T Base type to use (float, double) [double]
     * \tparam T_isConst True if this is a const reference [false]
     */
    template< typename T, bool T_isConst >
    struct ComplexRef
    {
        using type = T;
        static constexpr bool isConst = T_isConst;
        static constexpr bool isComplex = true;
        using Real_t = std::conditional_t< isConst, const Real<T>, Real<T> >;
        using Complex_t = std::conditional_t< isConst, const Complex<T>, Complex<T> >;

        Real_t &real;
        Real_t &imag;

        explicit ComplexRef(Complex_t& value): real(value.real), imag(value.imag){}
        ComplexRef(Real_t& r, Real_t& i): real(r), imag(i){}

        ComplexRef&
        operator=(const Complex_t& c){
            real = c.real;
            imag = c.imag;
            return *this;
        }
    };

}  // namespace types
}  // namespace foobar

template<typename T>
std::ostream& operator<< (std::ostream& stream, foobar::types::Complex<T> val){
    stream << val.real << " " << val.imag;
    return stream;
}

template<typename T, bool T_isConst>
std::ostream& operator<< (std::ostream& stream, foobar::types::ComplexRef<T, T_isConst> val){
    stream << foobar::types::Complex<T>(val);
    return stream;
}

namespace std {

    template< typename T, bool T_isConst >
    struct is_const< foobar::types::ComplexRef<T, T_isConst> >: std::integral_constant< bool, T_isConst >{};

    template< typename T, bool T_isConst >
    struct is_lvalue_reference< foobar::types::ComplexRef<T, T_isConst> >: std::true_type{};

}  // namespace std
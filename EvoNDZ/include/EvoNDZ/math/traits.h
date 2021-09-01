#pragma once
#include "concepts.h"

namespace evo::math
{
	namespace detail
	{
		template<typename T>
		struct number_value { using type = typename T::value_type; };

		template<Number T>
		struct number_value<T> { using type = T; };
	}

	template<typename T> 
	struct Traits { 
		using number_type = typename detail::number_value<T>::type; /*std::conditional_t<Number<T>, T, typename T::value_type>;*/

		constexpr static T summation_identity() requires HasSummationIdentity<T> {
			/*requires { { T::summation_identity() } -> std::convertible_to<T>; }*/
			if constexpr (detail::HasCustomSummationIdentity<T>) {
				return T::summation_identity();
			}
			else {
				return 0;
			}
		}

		constexpr static T multiplication_identity() requires HasMultiplicationIdentity<T> {
			/*requires { { T::multiplication_identity() } -> std::convertible_to<T>; }*/
			if constexpr (detail::HasCustomMultiplicationIdentity<T>) {
				return T::multiplication_identity(); 
			}
			else {
				return 1;
			}
		}
	};
}
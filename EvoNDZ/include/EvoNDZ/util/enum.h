#pragma once
#include <concepts>
#include <optional>

namespace evo
{
	// Flags paired with boolean values, requires T to be derived from Flags<T, *> struct.
	template<typename T>
	struct BooleanFlags {
		using value_type = typename T::value_type;

		constexpr BooleanFlags(const T flags, const bool value = true) 
			: m_flags(flags.m_value), m_bools(flags.m_value & ( value ? ~value_type(0) : 0 )) { }

		constexpr BooleanFlags operator|(const BooleanFlags other) const {
			return { m_flags | other.m_flags, ( m_bools & ~other.m_flags ) | ( other.m_bools & other.m_flags ) };
		}

		constexpr std::optional<bool> at(const T flag) const { 
			value_type mask = flag.m_value;
			if (mask & m_flags) {
				return m_bools & mask;
			}
			return std::nullopt;
		}

	private:
		value_type m_flags;
		value_type m_bools;

		constexpr BooleanFlags(const value_type flags, const value_type bools) : m_flags(flags), m_bools(bools) { }
	};

	//To create enum-like struct with available bitwise operations,
	//derive it from Flags<{MyEnum}, {optional base data type}>,
	//inside struct write EVO_FLAGS({MyEnum}) in the beginning, then EVO_FLAGS_E({Name}, {Index}) to create enum entry.
	//"None" entry is always created and it's value is 0.
	template<typename T, std::unsigned_integral V = uint64_t>
	struct Flags {
	private:
		using entry_function_type = T(*)( );

		friend struct BooleanFlags<T>;

	public:
		using value_type = V;

		constexpr BooleanFlags<T> with(const bool value) const {
			return BooleanFlags<T>(T(m_value), value);
		}

		constexpr T operator|(const T other) const {
			return m_value | other.m_value;
		}

		constexpr bool operator&(const T other) const {
			return m_value & other.m_value;
		}

		// sadly impossible
		/*constexpr friend T operator|(const entry_function_type a, const entry_function_type b) {
			return a() | b();
		}*/

		// vvv Useless/ambiguous? 

		constexpr friend T operator|(const T a, const entry_function_type b) {
			return a | b();
		}

		constexpr friend T operator|(const entry_function_type a, const T b) {
			return a() | b;
		}

		constexpr friend bool operator&(const T a, const entry_function_type b) {
			return a & b();
		}

		constexpr friend bool operator&(const entry_function_type a, const T b) {
			return a() & b;
		}

	protected:
		constexpr Flags(V e) : m_value(e) { }

		using enum_type = T;

	private:
		V m_value;
	};
}

#define EVO_FLAGS_E(Name, Index) constexpr static enum_type Name() { return 1ull << (Index); }

#define EVO_FLAGS(T)		private:														\
							friend struct Flags<T, value_type>;						\
							friend struct BooleanFlags<T>;							\
							constexpr T(const value_type value) : Flags(value) { }	\
						public:														\
							constexpr static enum_type None() { return 0ull; }
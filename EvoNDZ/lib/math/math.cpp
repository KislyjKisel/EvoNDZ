#include <iostream>
#include "../../include/EvoNDZ/math/vector2.h"
#include "../../include/EvoNDZ/math/vector3.h"
#include "../../include/EvoNDZ/math/vector4.h"

namespace evo
{
	template<std::floating_point T>
	std::ostream& operator<<(std::ostream& output, const Vector2<T> v) noexcept {
		output << '(' << v.x << ", " << v.y << ')';
		return output;
	}
	template<std::floating_point T>
	std::istream& operator>>(std::istream& input, Vector2<T>& v) noexcept {
		input >> v.x >> v.y;
		return input;
	}

	template std::ostream& operator<<(std::ostream&, const Vector2<float> v);
	template std::ostream& operator<<(std::ostream&, const Vector2<double> v);
	template std::ostream& operator<<(std::ostream&, const Vector2<long double> v);
	template std::istream& operator>>(std::istream&, Vector2<float>& v);
	template std::istream& operator>>(std::istream&, Vector2<double>& v);
	template std::istream& operator>>(std::istream&, Vector2<long double>& v);

	template<std::floating_point T>
	std::ostream& operator<<(std::ostream& output, const Vector3<T>& v) noexcept {
		output << v.x << ' ' << v.y << ' ' << v.z;
		return output;
	}
	template<std::floating_point T>
	std::istream& operator>>(std::istream& input, Vector3<T>& v) noexcept {
		input >> v.x >> v.y >> v.z;
		return input;
	}

	template std::ostream& operator<<(std::ostream&, const Vector3<float>& v);
	template std::ostream& operator<<(std::ostream&, const Vector3<double>& v);
	template std::ostream& operator<<(std::ostream&, const Vector3<long double>& v);
	template std::istream& operator>>(std::istream&, Vector3<float>& v);
	template std::istream& operator>>(std::istream&, Vector3<double>& v);
	template std::istream& operator>>(std::istream&, Vector3<long double>& v);

	template<std::floating_point T>
	std::ostream& operator<<(std::ostream& output, const Vector4<T>& v) noexcept {
		output << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w;
		return output;
	}
	template<std::floating_point T>
	std::istream& operator>>(std::istream& input, Vector4<T>& v) noexcept {
		input >> v.x >> v.y >> v.z >> v.w;
		return input;
	}

	template std::ostream& operator<<(std::ostream&, const Vector4<float>& v);
	template std::ostream& operator<<(std::ostream&, const Vector4<double>& v);
	template std::ostream& operator<<(std::ostream&, const Vector4<long double>& v);
	template std::istream& operator>>(std::istream&, Vector4<float>& v);
	template std::istream& operator>>(std::istream&, Vector4<double>& v);
	template std::istream& operator>>(std::istream&, Vector4<long double>& v);
}
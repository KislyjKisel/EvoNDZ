#include <iostream>
#include "../../include/EvoNDZ/util/color3.h"
#include "../../include/EvoNDZ/util/color4.h"

namespace evo
{
	template<std::floating_point T>
	std::ostream& operator<<(std::ostream& output, const Color3<T>& c) {
		output << c.r << ' ' << c.g << ' ' << c.b;
		return output;
	}
	template<std::floating_point T>
	std::istream& operator>>(std::istream& input, Color3<T>& c) {
		input >> c.r >> c.g >> c.b;
		return input;
	}

	template std::ostream& operator<<(std::ostream& output, const Color3<float>& c);
	template std::ostream& operator<<(std::ostream& output, const Color3<double>& c);
	template std::ostream& operator<<(std::ostream& output, const Color3<long double>& c);
	template std::istream& operator>>(std::istream& input, Color3<float>& c);
	template std::istream& operator>>(std::istream& input, Color3<double>& c);
	template std::istream& operator>>(std::istream& input, Color3<long double>& c);

	template<std::floating_point T>
	std::ostream& operator<<(std::ostream& output, const Color4<T>& c) {
		output << c.r << ' ' << c.g << ' ' << c.b << ' ' << c.a;
		return output;
	}
	template<std::floating_point T>
	std::istream& operator>>(std::istream& input, Color4<T>& c) {
		input >> c.r >> c.g >> c.b >> c.a;
		return input;
	}

	template std::ostream& operator<<(std::ostream& output, const Color4<float>& c);
	template std::ostream& operator<<(std::ostream& output, const Color4<double>& c);
	template std::ostream& operator<<(std::ostream& output, const Color4<long double>& c);
	template std::istream& operator>>(std::istream& input, Color4<float>& c);
	template std::istream& operator>>(std::istream& input, Color4<double>& c);
	template std::istream& operator>>(std::istream& input, Color4<long double>& c);
}
#pragma once
#include <variant>
#include <string>
#include <cassert>

using namespace std;

inline void VariantDemo()
{
	variant<int, float> v = 12; // v contains int
	//v = 15.5f; // Меняет тип.
	auto i = get<int>(v);
	variant<int, float> w = get<int>(v);
	// ReSharper disable once CppAssignedValueIsNeverUsed
	w = get<0>(v); // same effect as the previous line
	w = v; // same effect as the previous line

	auto flt = get<float>(v);

	//  get<double>(v); // error: no double in [int, float]
	//  get<3>(v);      // error: valid index values are 0 and 1

	try {
		auto t = get<float>(w); // w contains int, not float: will throw
	}
	catch (const bad_variant_access&) {}

	using namespace literals;

	variant<string> x("abc");
	// converting constructors work when unambiguous
	x = "def"; // converting assignment also works when unambiguous

	variant<string, void const*> y("abc");
	// casts to void const * when passed a char const *
	assert(holds_alternative<void const*>(y)); // succeeds
	y = "xyz"s;
	assert(holds_alternative<string>(y)); // succeeds
	// auto iop = holds_alternative_t<string>(y); // Не существует.
}
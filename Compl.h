#pragma once
#include <iso646.h>  // NOLINT(modernize-deprecated-headers, hicpp-deprecated-headers)

inline void ComplDemo()
{
	// ReSharper disable once CppDeclaratorNeverUsed
	unsigned int i = ~100 | compl 200; // compl = "~".
}
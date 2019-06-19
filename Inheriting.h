#pragma once

struct C // Forward declaration не скомпилится.
{
	int aa; // public в классе D. По умолчанию public-наследование.
};

struct D : C
{
	int bb;
};

inline void InheritingDemo()
{
	D d{};
	d.aa = 1;
}
#pragma once

void CastingDemo()
{
	unsigned int ui = 0xFFFFFFFF;
	int i = static_cast<int>(ui);
	// int a = reinterpret_cast<int>(ui); // ������.
	// unsigned int b = reinterpret_cast<unsigned int>(i); // ������.
}
#pragma once
#include <cstdint>
#include <cstring>
#include <memory>
#include <iostream>

using namespace std;

struct alignas(16) Bar
{
	int I;                  // 4 bytes
	int N;                  // 4 bytes
	alignas(4) char Arr[3];
	short S;                // 2 bytes
};

struct alignas(16) Bar1
{
	int I;                  // 4 bytes
	int N;                  // 4 bytes
	alignas(16) char Arr[3];
	alignas(2) short S;     // 2 bytes
};

void AlignAsDemo1();

class alignas(32) TstSomeClass
{
};

inline void AlignAsDemo()
{
	const auto some = make_unique<TstSomeClass>();
	const bool isProperlyAligned = reinterpret_cast<size_t>(some.get()) % 32 == 0;
	cout << boolalpha << isProperlyAligned << "\n"; // True.

	alignas(64) Bar1 af {};
	const auto pointer = reinterpret_cast<size_t>(&af);
	cout << "alignas(64) Bar1 af = " << (pointer % 64 == 0) << endl;

	// ReSharper disable once CppDeclaratorNeverUsed
	auto a = alignof(Bar); // output: 16
	// ReSharper disable once CppDeclaratorNeverUsed
	auto s1 = sizeof(Bar);
	// ReSharper disable once CppDeclaratorNeverUsed
	auto s2 = sizeof(Bar1);
	// ReSharper disable once CppDeclaratorNeverUsed
	auto s3 = sizeof(TstSomeClass);

	uint8_t mas[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B /* Невостребованный байт. */, 0x0C, 0x0D };
	Bar* pBar = reinterpret_cast<Bar*>(mas);
	// ReSharper disable once CppDeclaratorNeverUsed
	int i = pBar->I;
	// ReSharper disable once CppDeclaratorNeverUsed
	int n = pBar->N;
	char arr[3];
	memcpy(arr, pBar->Arr, 3);
	// ReSharper disable once CppDeclaratorNeverUsed
	short int s = pBar->S;

	pBar->I = 0;
	pBar->N = 1;
	pBar->Arr[0] = 2;
	pBar->Arr[1] = 3;
	pBar->Arr[2] = 4;
	pBar->S = 5;

	AlignAsDemo1();
}

inline void AlignAsDemo1()
{
	uint8_t mas[sizeof(Bar1)];
	for (size_t k = 0; k < sizeof(Bar1); k++)
		mas[k] = static_cast<uint8_t>(k);
	// ReSharper disable once CppDeclaratorNeverUsed
	Bar1* ptr = reinterpret_cast<Bar1*>(mas);
}
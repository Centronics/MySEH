#pragma once
#include <new>
#include <memory>

using namespace std;

class A
{
public:
	unsigned int I = 10; // ���������� �� ����� �������� ����������� ����.

	~A()
	{
		I = 90;
	}
};

inline void D1()
{
	const unique_ptr<char[]> chr(new char[10]);
	A* pa(new (chr.get()) A());
	A* pb(new (chr.get() + sizeof(A)) A); // ����� ������ � "A" ������ "A()".
	pa->I = 0xAAAAAAAA;
	pb->I = 0xBBBBBBBB;
	// chr[10] = 1; // �����.
	// pb[1] = A(); // ������, �.�. �� ������.
	pb->~A();
	pa->~A();
}

inline void D2()
{
	const unique_ptr<char[]> chr(new char[10]);
	A* pa(new (chr.get()) A());
	const A* pb(new (chr.get() + sizeof(A)) A());
	pa->I = 0xAAAAAAAA;
	// pb->I = 0xBBBBBBBB; // ��������� ������ ��������.
	pb->~A();
	pa->~A();
}

inline void PlacementNewDemo()
{
	D1();
	D2();
}
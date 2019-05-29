#pragma once

class A
{
public:
	int a = 1;
};

inline A& GetA()
{
	A* a = new A();
	a->a++;
	return *a;
}

inline void PointerExample()
{
	A* a = &GetA();
	a->a++;
	delete a;
}
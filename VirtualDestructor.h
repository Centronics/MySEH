#include <iostream>
using namespace std;

// ��������������� �����
class Object
{
public:
	Object() { cout << "Object::ctor()" << endl; }
	~Object() { cout << "Object::dtor()" << endl; }
};

// ������ ��������������� �����
class Object1
{
public:
	Object1() { cout << "Object1::ctor()" << endl; }
	~Object1() { cout << "Object1::dtor()" << endl; }
};

// ������� �����
class Base
{
public:
	Base() { cout << "Base::ctor()" << endl; }
	virtual ~Base()
	{
		cout << "Base::dtor()" << endl;
		Print();
	}
	virtual void demo()
	{
		__asm nop;
	}
	virtual void print() = 0;
	virtual void demo2() = 0;
	virtual void Print()
	{
		cout << "Print from Base." << endl;
	}
	void demo3()
	{
		__asm nop;
	}
};

// ����������� �����
class Derived : public Base
{
public:
	Derived() { cout << "Derived::ctor()" << endl; }
	~Derived()
	{
		Derived::Print(); // ����� ��������� ����������.
		cout << "Derived::dtor()" << endl;
	}
	void print()
	{
		__asm nop;
	}
	void Print() override
	{
		cout << "Print from Derived." << endl;
	}
	void demo2()
	{
		__asm nop;
	}
	Object  obj;
};

class Derived1 : public Derived
{
public:
	Derived1() { cout << "Derived1::ctor()" << endl; }
	~Derived1() { cout << "Derived1::dtor()" << endl; }

	Object1 obj;
};

class Parent
{
public:

	virtual void print()
	{
		std::cout << "������������ �����" << std::endl;
	}

	virtual void pa()
	{

	}
};

class DerivedFromParent : public Parent
{
public:

	virtual void print(int x)
	{
		std::cout << "����������� �����" << std::endl;
	}
};

static void VirtualDestructorStart()
{
	{
		DerivedFromParent* derived = new DerivedFromParent;
		//derived->print(); // ������, �.�. ���������� ��������������� ������ print, �������� �� ���������, ��� �� ������� �� virtual
		derived->pa(); // ���������
	}

	int x = sizeof(Base);
	int y = sizeof(Derived);
	int z = sizeof(Derived1);
	Base * p = new Derived1;
	p->print();
	p->demo();
	p->demo2();
	p->demo3();
	p->Print();
	delete p;
}

/*
� ����� ���������������� C++ ���������� ������������ �������� ������ ������ ����������� �����������.
������ ��� �������������� ���������� ���������� ������� ������������ ������ ����� ��������� �� ��������������� ������� �����.
� ������� main ��������� �� ������� ����� ������������� ����� ����������� ������������ ������� ������������ ������ Derived. ����� ����� ���� ��������� ������ �����������.
��� ���� ������� ������������ ����������� �������� ������ ������������ ������ ������������ ���� ������� � ��������� �������, � ������, � �������,
�������� ������� ������������� ��������������� �������.
����� ��������� � �������������� ������������ ����������� � ������� ������ ����� ���������:

Base::ctor()
Object::ctor()
Derived::ctor()
Derived::dtor()
Object::dtor()
Base::dtor()

����������� ������� ������������ ������ ����� ��������� �� ������� ����� � ������������� ������������ ���� �������������� ���������.
�� �������� ��� ���������� � ���, ��� ����� ��������� ������ ����� �������, ��������������� �������� ������.
���� � ���� ���� ������ �������� ����� virtual ����� ������������ �������� ������, �� ����� ��������� ����� ��� ����.
�������� ��������, ��� ���� ������ obj ������ Derived ����� �� �����������.

Base::ctor()
Object::ctor()
Derived::ctor()
Base::dtor()

����� �� ������� ��������� ���������� �����������? C��������� ������� - ���� ������� ����� ������������ ��� ������������ �������������,
�� ��� ���������� ������ ����������� �����������. ��� ���������� ��������� ����������� ������� ������ ������ ������ ������ ��������� ��
������� ����������� ������� vptr, ��� ����������� ��� ����� ������. ������, ��� ���������� ������������ ����������� ����� ����� ��� �����
����������� �������, � ���������� ������� ���������������� ������� �� ����������.

���� �� ������� ����� �� ������������ ��� ������������ ������������� (�� �������� ����������� �������), �� ��� ���������� �� ������ ����������� �����������.
*/
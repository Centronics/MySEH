#include <iostream>
using namespace std;

// Вспомогательный класс
class Object
{
public:
	Object() { cout << "Object::ctor()" << endl; }
	~Object() { cout << "Object::dtor()" << endl; }
};

// Второй вспомогательный класс
class Object1
{
public:
	Object1() { cout << "Object1::ctor()" << endl; }
	~Object1() { cout << "Object1::dtor()" << endl; }
};

// Базовый класс
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

// Производный класс
class Derived : public Base
{
public:
	Derived() { cout << "Derived::ctor()" << endl; }
	~Derived()
	{
		Derived::Print(); // Можно разрулить статически.
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
		std::cout << "Родительский класс" << std::endl;
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
		std::cout << "Производный класс" << std::endl;
	}
};

static void VirtualDestructorStart()
{
	{
		DerivedFromParent* derived = new DerivedFromParent;
		//derived->print(); // Ошибка, т.к. происходит переопределение метода print, несмотря на сигнатуру, это не зависит от virtual
		derived->pa(); // нормально
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
В языке программирования C++ деструктор полиморфного базового класса должен объявляться виртуальным.
Только так обеспечивается корректное разрушение объекта производного класса через указатель на соответствующий базовый класс.
В функции main указателю на базовый класс присваивается адрес динамически создаваемого объекта производного класса Derived. Затем через этот указатель объект разрушается.
При этом наличие виртуального деструктора базового класса обеспечивает вызовы деструкторов всех классов в ожидаемом порядке, а именно, в порядке,
обратном вызовам конструкторов соответствующих классов.
Вывод программы с использованием виртуального деструктора в базовом классе будет следующим:

Base::ctor()
Object::ctor()
Derived::ctor()
Derived::dtor()
Object::dtor()
Base::dtor()

Уничтожение объекта производного класса через указатель на базовый класс с невиртуальным деструктором дает неопределенный результат.
На практике это выражается в том, что будет разрушена только часть объекта, соответствующая базовому классу.
Если в коде выше убрать ключевое слово virtual перед деструктором базового класса, то вывод программы будет уже иным.
Обратите внимание, что член данных obj класса Derived также не разрушается.

Base::ctor()
Object::ctor()
Derived::ctor()
Base::dtor()

Когда же следует объявлять деструктор виртуальным? Cуществует правило - если базовый класс предназначен для полиморфного использования,
то его деструктор должен объявляться виртуальным. Для реализации механизма виртуальных функций каждый объект класса хранит указатель на
таблицу виртуальных функций vptr, что увеличивает его общий размер. Обычно, при объявлении виртуального деструктора такой класс уже имеет
виртуальные функции, и увеличения размера соответствующего объекта не происходит.

Если же базовый класс не предназначен для полиморфного использования (не содержит виртуальных функций), то его деструктор не должен объявляться виртуальным.
*/
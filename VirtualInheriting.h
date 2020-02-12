class GC
{
public:
	virtual ~GC() {} // можно default
	int Hj = 9;

	virtual void CupFunc()
	{
		__asm nop;
	}
};

class D : public GC
{
public:
	D()
	{
		__asm nop;
	}
	~D()
	{
		__asm nop;
	}
	virtual void CupFunc()
	{
		__asm nop;
	}
};

class C : virtual public D
{
public:
	virtual void foo()
	{
		Hj = 200;
	}
	C()
	{
		__asm nop;
	}
	~C()
	{
		__asm nop;
	}
};

class F : virtual public D
{
public:
	virtual char foo(int)
	{
		Hj = 100;
		return 0;
	}
	F()
	{
		__asm nop;
	}
	~F()
	{
		__asm nop;
	}
};

class Cl : public F, public C
{
public:
	virtual void foo(char w)
	{
		if (w) F::foo(1);
		else C::foo();
		Hj = 10;
	}
	Cl()
	{
		foo('L');
		__asm nop;
	}
	~Cl()
	{
		__asm nop;
	}
};

class l2
{

};

class Lock
{
	/*friend class Foo;
	Lock() { }
	Lock(const Lock&) { }*/
};

class Foo : private Lock, l2 // Чтобы не компилилось, надо написать virtual private
{

};

class Bar : public Foo
{

};

void VirtualInheritStart()
{
	{
		Foo foo;
		Bar bar;
	}

	{
		F f; // тоже можно
		f.Hj = 20;
		f.foo(2);
		f.CupFunc();
	}
	Cl myc;
	myc.CupFunc();
	myc.GC::CupFunc();
	myc.foo(1);
	myc.foo(0);
}


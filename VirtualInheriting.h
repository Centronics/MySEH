class GC
{
public:
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
	virtual void foo(){}
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
	virtual char foo(int){return 0;}
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
		if(w) F::foo(1);
		else C::foo();
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

void VirtualInheritStart()
{
	Cl myc;
	myc.CupFunc();
	myc.GC::CupFunc();
	myc.foo(1);
	myc.foo(0);
}
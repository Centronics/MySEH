class B { };
class D : private B { friend class Derived; };
struct Base {
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
	virtual B* vf4();
	virtual B* vf5();
	void f();
};

struct No_good : public Base {
	D* vf4(); // error: B (base class of D) inaccessible
};

class A;

struct Derived : public Base {
	void vf1(); // virtual and overrides Base::vf1()
	void vf2(int); // not virtual, hides Base::vf2()
	char vf3(); // error: invalid difference in return type only
	D* vf4(); // OK: returns pointer to derived class
	A* vf5(); // error: returns pointer to incomplete class
	void f();
};

void g()
{
	Derived d;
	Base* bp = &d; // standard conversion:
	// Derived* to Base*
	bp->vf1(); // calls Derived::vf1()
	bp->vf2(); // calls Base::vf2()
	bp->f(); // calls Base::f() (not virtual)
	B* p = bp->vf4(); // calls Derived::pf() and converts the
	// result to B*
	Derived* dp = &d;
	D* q = dp->vf4(); // calls Derived::pf() and does not
	// convert the result to B*
	dp->vf2(); // ill-formed: argument mismatch
}
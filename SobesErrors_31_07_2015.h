#pragma once
#include <iostream>
#include <string>

using namespace std;

/*class X
{
	int _private;

protected:
	int _protected;

public:
	int _public;
};

// Вывод следующий: модификатор доступа переменной отражает возможность "прыжка" до определённого уровня, а модификатор доступа наследования - говорит "до куда" можно "прыгнуть". Отталкиваться нужно от модификатора доступа в базовом классе.

class Private : X
{
protected:

	void Method()
	{
		_private = 10;
		_protected = 10;
		_public = 10;
	}
};

class Protected : protected X
{
protected:

	void Method()
	{
		_private = 10;
		_protected = 10;
		_public = 10;
	}
};

class Public : public X
{
protected:

	void Method()
	{
		_private = 10;
		_protected = 10;
		_public = 10;
	}
};

///////////////////

class XPublic : public Private
{
protected:

	void Test()
	{
		_private = 10;
		_protected = 10;
		_public = 10;
	}
};

class XProtected : protected Private
{
protected:

	void Test()
	{
		_private = 10;
		_protected = 10;
		_public = 10;
	}
};

class XPrivate : Private
{
protected:

	void Test()
	{
		_private = 10;
		_protected = 10;
		_public = 10;
	}
};

///////////////////

class YPublic : public Protected
{
protected:

	void Test()
	{
		_private = 10;
		_protected = 10;
		_public = 10;
	}
};

class YProtected : protected Protected
{
protected:

	void Test()
	{
		_private = 10;
		_protected = 10;
		_public = 10;
	}
};

class YPrivate : Protected
{
protected:

	void Test()
	{
		_private = 10;
		_protected = 10;
		_public = 10;
	}
};

///////////////////

class ZPublic : public Public
{
protected:

	void Test()
	{
		_private = 10;
		_protected = 10;
		_public = 10;
	}
};

class ZProtected : protected Public
{
protected:

	void Test()
	{
		_private = 10;
		_protected = 10;
		_public = 10;
	}
};

class ZPrivate : Public
{
protected:

	void Test()
	{
		_private = 10;
		_protected = 10;
		_public = 10;
	}
};*/

inline void ValueTest()
{
	int A = 128;
	char B = A;
	A = B; // -128
}

void print(int v)
{
	cout << "int: " << v << endl;
}

void print(bool v)
{
	cout << "bool: " << v << endl;
}

void print(string v)
{
	cout << "std::string: " << v << endl;
}

/*class CFoo
{
	int cachedValue;
	bool bCached;

public:
	int calculate() const
	{
		if (bCached)
			return cachedValue;
		cachedValue = 5;
		bCached = true;
	}
};*/

inline void Sobes_31_07_2015()
{
	/*CFoo cfoo;
	cfoo.calculate();*/

	print(1); // int
	print(true); // bool
	print("Hello world"); // bool

	ValueTest();

	/*Public pub;
	pub._public = 10; // public
	pub._protected = 10;
	pub._private = 10;

	Protected pro;
	pro._public = 10;
	pro._protected = 10;
	pro._private = 10;

	Private pri;
	pri._public = 10;
	pri._protected = 10;
	pri._private = 10;

	XPublic xp;
	xp._public = 10;
	xp._protected = 10;
	xp._private = 10;

	XProtected xr;
	xr._public = 10;
	xp._protected = 10;
	xp._private = 10;

	XPrivate xt;
	xt._public = 10;
	xp._protected = 10;
	xp._private = 10;

	YPublic yp;
	yp._public = 10;
	xp._protected = 10;
	xp._private = 10;

	YProtected yr;
	yr._public = 10;
	xp._protected = 10;
	xp._private = 10;

	YPrivate yt;
	yt._public = 10;
	xp._protected = 10;
	xp._private = 10;

	ZPublic zp;
	zp._public = 10;  // public
	xp._protected = 10;
	xp._private = 10;

	ZProtected zr;
	zr._public = 10;
	xp._protected = 10;
	xp._private = 10;

	ZPrivate zt;
	zt._public = 10;
	xp._protected = 10;
	xp._private = 10;*/
}
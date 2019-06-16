#pragma once
#include <algorithm>

using namespace std;

struct A
{
    A(int) { }      // converting constructor
    A(int, int) { } // converting constructor (C++11)
    operator bool() const { return true; }
};
 
struct B
{
    explicit B(int) { }
    explicit B(int, int) { }
    explicit operator bool() const { return true; }
};

struct C
{
	int a;
	int&& r;
};

struct D { explicit D(int i = 0) {} double d; };

inline int F(){return 0;} // Препроцессор не всегда автоматически возвращает значение.

inline void ExplicitDemo()
{
    A a1 = 1;      // OK: copy-initialization selects A::A(int)
    A a2(2);       // OK: direct-initialization selects A::A(int)
    A a3 {4, 5};   // OK: direct-list-initialization selects A::A(int, int)
    A a4 = {4, 5}; // OK: copy-list-initialization selects A::A(int, int)
    A a5 = (A)1;   // OK: explicit cast performs static_cast
    if (a1) ;      // OK: A::operator bool()
    bool na1 = a1; // OK: copy-initialization selects A::operator bool()
    bool na2 = static_cast<bool>(a1); // OK: static_cast performs direct-initialization
	A a6 = 1.2f;
 
//  B b1 = 1;      // error: copy-initialization does not consider B::B(int)
    B b2(2);       // OK: direct-initialization selects B::B(int)
    B b3 {4, 5};   // OK: direct-list-initialization selects B::B(int, int)
//  B b4 = {4, 5}; // error: copy-list-initialization does not consider B::B(int,int)
    B b5 = (B)1;   // OK: explicit cast performs static_cast
    if (b2) ;      // OK: B::operator bool()
//  bool nb1 = b2; // error: copy-initialization does not consider B::operator bool()
    bool nb2 = static_cast<bool>(b2); // OK: static_cast performs direct-initialization
	B b6 {static_cast<int>(1.2f)};

	int n = 10;

	B c1{ 1, F() };             // OK, lifetime is extended
	B c2(1, F());               // well-formed, but dangling reference
	B c3{static_cast<int>(1.0), 1 };             // error: narrowing conversion
	B c4(1.0, 1);               // well-formed, but dangling reference
	B c5(1.0, move(n));         // OK

	// D d[2]( D(1) ); // OK: initializes a[0] with A(1) and a[1] with A() // Так писать нельзя.
	D v[2]{ D(1) }; // error; implicit copy-list-initialization of a[1] from {} selected explicit constructor. Переменная "d" НЕ будет инициализирована.

	int t[20]{10}; // Так писать можно. Первый элемент будет 10, остальные 0.
}
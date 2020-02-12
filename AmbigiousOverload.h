#pragma once
#include "string"

using namespace std;

void fgfunc(string str);
//void func(string str); // неоднозначность
void func(const string& str); // для вызова надо, чтобы бал const, иначе ошибка
void func(string& str);

inline void AmbigiousOverloadExample()
{
	fgfunc("1");
	func("2");
	func(string());
	func(reinterpret_cast<char*>("23"));
}
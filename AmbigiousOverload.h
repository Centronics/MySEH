#pragma once
#include "string"

using namespace std;

void fgfunc(string str);
//void func(string str); // ���������������
void func(const string& str); // ��� ������ ����, ����� ��� const, ����� ������
void func(string& str);

inline void AmbigiousOverloadExample()
{
	fgfunc("1");
	func("2");
	func(string());
	func(reinterpret_cast<char*>("23"));
}
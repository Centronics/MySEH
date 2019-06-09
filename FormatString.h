#pragma once
#include <cassert>
#include <string>

using namespace std;

inline void FormatStringDemo()
{
	string s = "but I have heard it works even if you don't believe in it";
	s.replace(0, 4, "") // ���� ���-�� �� �������, �� ����� ���� ����������.
		.replace(s.find("even"), 4, "only")
		.replace(s.find(" don't"), 6, "");

	assert(s == "I have heard it works only if you believe in it");

	// ���������� ��� ������ ����������.
	s = "but I have heard it works even if you don't believe in it";
	s.replace(0, 4, ""); // ���� ���-�� �� �������, �� ����� ���� ����������.
	s.replace(s.find("even"), 4, "only");
	s.replace(s.find(" don't"), 6, "");

	assert(s == "I have heard it works only if you believe in it");
}
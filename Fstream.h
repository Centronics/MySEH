#pragma once
#include <fstream>

using namespace std;

inline void FstreamTest()
{
	ifstream s("D:\\PriceList.dat", ios::binary | ios::ate);
	if (!s.is_open())
		return;

	ifstream::pos_type size = s.tellg();
	const long long sp = size;
	char c[3]; // ������ ������. ����, ����� ����� � ��������������� ����, ��� ������� �� �����!

	/*s >> c;
	bool b = s.eof();
	char t[2];
	s >> t;
	bool h = s.eof();

	char t1[4];
	s >> t1;
	bool h1 = s.eof();*/

	unsigned int i;
	s >> i;
	bool g = s.eof();

	unsigned int i1;
	s >> i1;
	bool g1 = s.eof();

	int* pint = new int[20];
	{
		unique_ptr<int[]> iop(new int[20]);
		iop[1] = 20;
	}
}
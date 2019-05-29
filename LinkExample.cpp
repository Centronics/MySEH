#include "LinkExample.h"

void link_use(int& l1, int& l2, float& l3)
{
  l1 = 100;
  l2 = 200;
  l3 = 0.3;
}

void point_use(int* l1, int* l2, float* l3)
{
  *l1 = 1000;
  *l2 = 2000;
  *l3 = 0.03;
}

void noret_use(int l1, int l2, float l3)
{
  l1 = 100;
  l2 = 200;
  l3 = 0.3;
}

void LinkExample()
{
	int i1=0, i2=0;
	float  i3=0;
	float& l3=i3;
	const  int& li2 = 10;

	link_use(i1, i2, i3);
	point_use(&i1, &i2, &i3);
	noret_use(i1, i2, i3);
}
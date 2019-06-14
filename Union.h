#pragma once

union Union
{
	unsigned long long lng;
	double dbl;
};

union Union1
{
	Union1()
	{
		flt = 0.0f;
	}

	unsigned long lng;
	float flt;
};

inline void UnionDemo()
{
	Union u;
	u.dbl = 8.0;

	Union1 u1;
	u1.flt = 0.25f;
}
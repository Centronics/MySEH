#pragma once

class Except
{
public:
	Except()
	{
		_asm int 3;
	}
	
	Except(Except& e)
	{
		_asm int 3;
	}

	~Except()
	{
		_asm int 3;
	}
};

inline void ExceptionConstructionStart()
{
	try
	{
		throw Except();
	}
	catch(Except e)
	{
		_asm int 3;
	}

	try
	{
		throw Except();
	}
	catch(Except& e)
	{
		_asm int 3;
	}
}
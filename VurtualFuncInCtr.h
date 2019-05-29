class VA
{
public:
	VA(int i)
	{
		f1();
	}
	int b;
	virtual void f1()
	{
		a = b = 0;
	}

protected:
	int a;
};

class VB : public VA
{
public:
	VB(int i) : VA(i)
	{

	}
	int c;

	void f1()
	{
		VA::f1();
	}
};

void VitrualFuncInCtr()
{
	VA* pa = new VB(0);
}
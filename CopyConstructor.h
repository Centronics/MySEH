class CpyA
{
public:
	CpyA& operator=(CpyA&);
	CpyA();
};

class CpyC
{
	int i;
public:
	CpyC();
};

class CpyB
{
	CpyA ca;
	CpyC cc;
public:
	CpyB();
	CpyB(CpyB&);
};

void CopyTestFunction();
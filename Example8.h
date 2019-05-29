class ClassInheritingA
{
public:
	int i, *ii;

	ClassInheritingA();
	virtual ~ClassInheritingA();
};

class ClassInheritingB : public ClassInheritingA
{
public:
	int A;

	~ClassInheritingB();
};

struct StructInheritingA
{
public:
	int i;

	//virtual ~StructInheritingA();
};

struct StructInheritingB : StructInheritingA
{
public:
	int A;

	~StructInheritingB();
};

class CNewClass
{
public:
	CNewClass();
	//~CNewClass();
};

void Example8();
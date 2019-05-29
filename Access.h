class Constructor
{
protected:

	static void StaticVoid(); //если protected, то недоступно
};

class Constructing : public Constructor
{

public:

	class Included
	{

	public:

		static void StatVoid();

	public:

		static void Incl();
	};

public:

	static void VoidIncluded();
};

void ExampleAccess();
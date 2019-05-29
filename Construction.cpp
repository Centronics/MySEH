#include "Construction.h"

cls1::cls1() : c(10)
{

}

cls1 clo;

void ExampleConstruction()
{
	cls1 cl1;
	cls1 cl3 = cls1();
	cls1* cly = new cls1();
}
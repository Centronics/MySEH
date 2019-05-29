#include "Access.h"

void Constructor::StaticVoid()
{

}

void Constructing::Included::Incl()
{
	VoidIncluded();
}

void Constructing::Included::StatVoid()
{

}

void Constructing::VoidIncluded()
{
	StaticVoid();
	Included::StatVoid();
}

void ExampleAccess()
{
	Constructing::VoidIncluded();
	Constructing::Included::Incl();
	//Constructing::StaticVoid();
}
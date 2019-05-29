#include "Example2.h"

TestClassTwo::TestClassTwo() //порождает аппаратное исключение
{
	int i = 0, j = 1;
	j /= i;
}

TestClassTwo::~TestClassTwo() //деструктор не выполнится
{
	int i = 0, j = 1;
	j /= i;
}

void Example2()
{
	TestClassTwo* tst = nullptr;
	try
	{
		tst = new TestClassTwo(); //деструктор не вызовется, память не будет очищена, если стоит "НЕТ" в настройках модели обработки исключений
								  //исключение перехватывается только если установлен либо \EHA, либо "НЕТ"
	}
	catch(...)
	{
		delete tst; //tst не будет инициализирован
	}
}
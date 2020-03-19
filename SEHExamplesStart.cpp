/*#include "ExampleOne.h"
#include "Example2.h"
#include "Example3.h"
#include "VirtualDestructor.h"
#include "VirtualInheriting.h"
#include "Example4.h"
#include "Example5.h"
#include "DestrException.h"
#include "ConstrException.h"
#include "Example6.h"
#include "LinkExample.h"
#include "DestrException2.h"
#include "Example7.h"
#include "IsVirtual.h"
#include "Overload.h"
#include "VurtualFuncInCtr.h"
#include "Example8.h"
#include "Access.h"
#include "Construction.h"
#include "CopyConstructor.h"
#include "typedefMas.h"
#include "ClassCopy.h"
#include "UniquePtr.h"
#include "PointerFromReference.h"
#include "DefaultConstructor.h"
#include "LambdaPointer.h"
#include "MoveConstructor.h"
#include "NoexceptExample.h"
#include "ProtectedConstructor.h"
#include "OperatorInheriting.h"
#include "ForEach.h"
#include "Alignas.h"
#include "Relatives.h"
#include "MapDemo.h"
#include "Decltype.h"
#include "Expression.h"
#include "FormatString.h"
#include "Template.h"
#include "StaticIntTest.h"
#include "DynamicTemplate.h"
#include "Switch.h"
#include "Any.h"
#include "Union.h"
#include "Equal.h"
#include "Narrow.h"
#include "Inheriting.h"
#include "KeepWindowOpen.h"
#include "Initialization.h"
#include "SobesErrors_31_07_2015.h"
#include "Explicit.h"
#include "VariableArguments.h"
#include "PlacementNew.h"
#include "Defaults.h"
#include "Casting.h"
#include "map.h"
#include "YandexSobesTest.h"
#include "ListOperations.h"
#include "STDThread.h"
#include "KasperskyProblemTest.h"
#include "KasperskyTest.h"
#include "OperatorOverload.h"*/

#include <Windows.h>
#include <memory>
#include "FINTECHTest.h"
int __cdecl main()
{
	try
	{
		LPTSTR pszBuf = (LPTSTR)LocalAlloc(LPTR, MAX_PATH * sizeof(TCHAR));
		//_asm int 3;
		PSECURITY_DESCRIPTOR pSD = (PSECURITY_DESCRIPTOR)GlobalAlloc(GMEM_MOVEABLE, sizeof(PSECURITY_DESCRIPTOR));
		//_asm int 3;

		MoveMemory(pszBuf, pSD, 1);

		//_asm int 3;

		std::unique_ptr<int> t[] = { std::unique_ptr<int>(new int(9)), std::unique_ptr<int>(new int(8)) };
		for (auto&& f : t) // от ссылки обычной или на R_Value ничего не меняется
		{
			int* gh = f.get();
			std::unique_ptr<int> h = move(f);
			_asm nop;
		}

		class A
		{
			int t;
		};

		class B : A
		{

		};

		const unsigned sd = sizeof(B);
		//const double sd1 = 5.0 / 0; // бесконечность

		HANDLE h = HeapCreate(0, 0, 8192);
		LPVOID v = HeapAlloc(h, HEAP_ZERO_MEMORY, 1024);

		unsigned char* mem = reinterpret_cast<unsigned char*>(v);

		for (unsigned r = 0; r < 1024; ++r)
			*mem++ = 0;

		LPVOID v1 = HeapAlloc(h, HEAP_ZERO_MEMORY, 2048); // если этого вызова не будет, последующий цикл будет слетать

		unsigned char* mem1 = reinterpret_cast<unsigned char*>(v);

		for (unsigned r = 0; r < 3000; ++r)
			*mem1++ = 0;

		unsigned char* p = (unsigned char*)VirtualAlloc(NULL, 8192, MEM_RESERVE, PAGE_READWRITE);
		p = (unsigned char*)VirtualAlloc(p, 4096, MEM_COMMIT, PAGE_READWRITE);

		for (unsigned r = 0; r < 4096; ++r) // не более 4096
			*p++ = 0;

		p = (unsigned char*)VirtualAlloc(p, 8192, MEM_COMMIT, PAGE_READWRITE);

		for (unsigned r = 0; r < 8192; ++r)
			*p++ = 0;

		int ui = 9;
		unsigned er = ui;
		ui = er;

		int* mas = 0;
		mas[100u] = 1;

		int arr[123] = { 10, 9 };
		int tmp = *(&arr + 1) - arr; // 123
		
		return 0;
	}
	catch (...)
	{
		return 1;
	}
}

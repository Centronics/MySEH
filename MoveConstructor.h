#pragma once
#include <algorithm>

using namespace std;

class ClsMove // ���� ���������� �����-���� ������� �� �������� "�������", �� ������������� ��������� ��������� � ������� ���������� ���� �� default. � ��� �����, ���������� �������������� Resharper.
{
public:
	void* _ptr = reinterpret_cast<void*>(111);

	/*ClsMove(ClsMove&& move) noexcept // ����� ������ ����������� �����������.
	{
		_ptr = nullptr; // ������� ���� ���������.
		_ptr = move._ptr;
		move._ptr = nullptr;
	}

	ClsMove& operator=(ClsMove&& move) noexcept
	{
		_ptr = nullptr; // ������� ���� ���������.
		_ptr = move._ptr;
		move._ptr = nullptr;
		return *this;
	}*/
};

class ClsMove1  // NOLINT(cppcoreguidelines-special-member-functions, hicpp-special-member-functions)
{
public:
	void* _ptr = reinterpret_cast<void*>(111);

	ClsMove1() = default; // ����������� �����. ����� ����������� �� ��������� ����� ��������� ��������.
	ClsMove1(ClsMove1&& move) noexcept// = default; // ����� ������ ����������� �����������.
	{
		_ptr = nullptr; // ������� ���� ���������.
		_ptr = move._ptr;
		move._ptr = nullptr;
	}

	ClsMove1& operator=(ClsMove1&& move) noexcept = default;
	/*{
		_ptr = nullptr; // ������� ���� ���������.
		_ptr = move._ptr;
		move._ptr = nullptr;
		return *this;
	}*/

	ClsMove1(const ClsMove1&)//=default; // ���� default - �������� ��� �� ���������.
	{

	}

	ClsMove1& operator=(const ClsMove1&) = default; // default - �������� �� ���������.
/*	{
		return *this;
	}*/

	// ������� ������� ����� �������, �� �� default.
};

inline ClsMove1 GetCls()
{
	return ClsMove1();
}

inline void SetCls(ClsMove1&& cls) // ������ ����� ������ ��� ����� ��� ������.
{
	cls._ptr = reinterpret_cast<void*>(3);
}

inline void SetCls(ClsMove1& cls)
{
	cls._ptr = reinterpret_cast<void*>(4);
}

inline void MoveConstructorDemo() // �� ��������� ����������� ����������� ��������������� ��� ����������� �����������.
{
	ClsMove cld;
	// ReSharper disable once CppDeclaratorNeverUsed
	ClsMove cls = move(cld); // ������ ����������� ����� �����������, ���� ��� ������������ ������������ �����������.  // NOLINT(performance-move-const-arg)

	ClsMove1 clr;
	ClsMove1 cle = move(clr); // ����� �����������.
	clr = move(cle); // ������������ �����������.
	cle = static_cast<ClsMove1&&>(clr); // �� ��, ��� � Move. ����������� ������������� �����������.
	clr = GetCls(); // ����������� ������������� �����������.
	clr._ptr = reinterpret_cast<void*>(88);
	// ReSharper disable once CppEntityAssignedButNoRead
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	ClsMove1 clw = static_cast<ClsMove1&>(clr);		  // ����������� ����������� ��� ����������� - � ����������� �� ����, ����� �������������� ���� �������. ����� ������������ static_cast. ������ ��� ��.
	// ReSharper disable once CppEntityAssignedButNoRead
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	ClsMove1 clq = static_cast<ClsMove1&&>(clw);	  // ����������� ����������� ��� ����������� - � ����������� �� ����, ����� �������������� ���� �������. ����� ������������ static_cast. ������ ��� ��.
	// ReSharper disable once CppEntityAssignedButNoRead
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	ClsMove1 cla = reinterpret_cast<ClsMove1&>(clq);  // ����������� ����������� ��� ����������� - � ����������� �� ����, ����� �������������� ���� �������. ����� ������������ static_cast. ������ ��� ��.
	// ReSharper disable once CppEntityAssignedButNoRead
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	const ClsMove1 clz = reinterpret_cast<ClsMove1&&>(cla); // ����������� ����������� ��� ����������� - � ����������� �� ����, ����� �������������� ���� �������. ����� ������������ static_cast. ������ ��� ��.
	// ReSharper disable once CppAssignedValueIsNeverUsed
	clr = static_cast<ClsMove1&>(clw);		 // ����������� ����������� ��� ����������� - � ����������� �� ����, ����� �������������� ���� �������. ����� ������������ static_cast. ������ ��� ��.
	// ReSharper disable once CppAssignedValueIsNeverUsed
	clw = static_cast<ClsMove1&&>(clr);		 // ����������� ����������� ��� ����������� - � ����������� �� ����, ����� �������������� ���� �������. ����� ������������ static_cast. ������ ��� ��.
	// ReSharper disable once CppAssignedValueIsNeverUsed
	clq = reinterpret_cast<ClsMove1&>(clw);  // ����������� ����������� ��� ����������� - � ����������� �� ����, ����� �������������� ���� �������. ����� ������������ static_cast. ������ ��� ��.
	// ReSharper disable once CppAssignedValueIsNeverUsed
	cla = reinterpret_cast<ClsMove1&&>(clq); // ����������� ����������� ��� ����������� - � ����������� �� ����, ����� �������������� ���� �������. ����� ������������ static_cast. ������ ��� ��.
	clq = clz;
	clq._ptr = reinterpret_cast<void*>(1);
	SetCls(reinterpret_cast<ClsMove1&&>(clq)); // ������ ���� � ��� ��.
	clq._ptr = reinterpret_cast<void*>(9);
	SetCls(static_cast<ClsMove1&&>(clq));	   // ������ ���� � ��� ��.
	clq._ptr = reinterpret_cast<void*>(5);
	SetCls(clq);							   // ������ ���� � ��� ��.
}
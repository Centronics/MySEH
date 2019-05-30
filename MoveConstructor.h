#pragma once
#include <algorithm>

using namespace std;

class ClsMove // Если появляются какие-либо функции из основной "четвёрки", то отсутствующие считаются удалёнными и требуют реализацию хотя бы default. В том числе, появляется предупреждение Resharper.
{
public:
	void* _ptr = reinterpret_cast<void*>(111);

	/*ClsMove(ClsMove&& move) noexcept // Будет вызван конструктор перемещения.
	{
		_ptr = nullptr; // Очищаем свой указатель.
		_ptr = move._ptr;
		move._ptr = nullptr;
	}

	ClsMove& operator=(ClsMove&& move) noexcept
	{
		_ptr = nullptr; // Очищаем свой указатель.
		_ptr = move._ptr;
		move._ptr = nullptr;
		return *this;
	}*/
};

class ClsMove1  // NOLINT(cppcoreguidelines-special-member-functions, hicpp-special-member-functions)
{
public:
	void* _ptr = reinterpret_cast<void*>(111);

	ClsMove1() = default; // Обязательно нужен. Иначе конструктор по умолчанию будет считаться удалённым.
	ClsMove1(ClsMove1&& move) noexcept// = default; // Будет вызван конструктор перемещения.
	{
		_ptr = nullptr; // Очищаем свой указатель.
		_ptr = move._ptr;
		move._ptr = nullptr;
	}

	ClsMove1& operator=(ClsMove1&& move) noexcept = default;
	/*{
		_ptr = nullptr; // Очищаем свой указатель.
		_ptr = move._ptr;
		move._ptr = nullptr;
		return *this;
	}*/

	ClsMove1(const ClsMove1&)//=default; // Если default - работает как по умолчанию.
	{

	}

	ClsMove1& operator=(const ClsMove1&) = default; // default - работает по умолчанию.
/*	{
		return *this;
	}*/

	// Обычные функции можно удалить, но не default.
};

inline ClsMove1 GetCls()
{
	return ClsMove1();
}

inline void SetCls(ClsMove1&& cls) // Объект будет изменён как будто это ссылка.
{
	cls._ptr = reinterpret_cast<void*>(3);
}

inline void SetCls(ClsMove1& cls)
{
	cls._ptr = reinterpret_cast<void*>(4);
}

inline void MoveConstructorDemo() // По умолчанию конструктор перемещения предоставляется как конструктор копирования.
{
	ClsMove cld;
	// ReSharper disable once CppDeclaratorNeverUsed
	ClsMove cls = move(cld); // Вместо перемещения будет копирование, если нет опеределения конструктора перемещения.  // NOLINT(performance-move-const-arg)

	ClsMove1 clr;
	ClsMove1 cle = move(clr); // Будет перемещение.
	clr = move(cle); // Присваивание перемещения.
	cle = static_cast<ClsMove1&&>(clr); // То же, что и Move. Срабатывает присваивающее перемещение.
	clr = GetCls(); // Срабатывает присваивающее перемещение.
	clr._ptr = reinterpret_cast<void*>(88);
	// ReSharper disable once CppEntityAssignedButNoRead
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	ClsMove1 clw = static_cast<ClsMove1&>(clr);		  // Срабатывает копирование или перемещение - в зависимости от того, какое преобразование было выбрано. Можно использовать static_cast. Эффект тот же.
	// ReSharper disable once CppEntityAssignedButNoRead
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	ClsMove1 clq = static_cast<ClsMove1&&>(clw);	  // Срабатывает копирование или перемещение - в зависимости от того, какое преобразование было выбрано. Можно использовать static_cast. Эффект тот же.
	// ReSharper disable once CppEntityAssignedButNoRead
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	ClsMove1 cla = reinterpret_cast<ClsMove1&>(clq);  // Срабатывает копирование или перемещение - в зависимости от того, какое преобразование было выбрано. Можно использовать static_cast. Эффект тот же.
	// ReSharper disable once CppEntityAssignedButNoRead
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	const ClsMove1 clz = reinterpret_cast<ClsMove1&&>(cla); // Срабатывает копирование или перемещение - в зависимости от того, какое преобразование было выбрано. Можно использовать static_cast. Эффект тот же.
	// ReSharper disable once CppAssignedValueIsNeverUsed
	clr = static_cast<ClsMove1&>(clw);		 // Срабатывает копирование или перемещение - в зависимости от того, какое преобразование было выбрано. Можно использовать static_cast. Эффект тот же.
	// ReSharper disable once CppAssignedValueIsNeverUsed
	clw = static_cast<ClsMove1&&>(clr);		 // Срабатывает копирование или перемещение - в зависимости от того, какое преобразование было выбрано. Можно использовать static_cast. Эффект тот же.
	// ReSharper disable once CppAssignedValueIsNeverUsed
	clq = reinterpret_cast<ClsMove1&>(clw);  // Срабатывает копирование или перемещение - в зависимости от того, какое преобразование было выбрано. Можно использовать static_cast. Эффект тот же.
	// ReSharper disable once CppAssignedValueIsNeverUsed
	cla = reinterpret_cast<ClsMove1&&>(clq); // Срабатывает копирование или перемещение - в зависимости от того, какое преобразование было выбрано. Можно использовать static_cast. Эффект тот же.
	clq = clz;
	clq._ptr = reinterpret_cast<void*>(1);
	SetCls(reinterpret_cast<ClsMove1&&>(clq)); // Эффект один и тот же.
	clq._ptr = reinterpret_cast<void*>(9);
	SetCls(static_cast<ClsMove1&&>(clq));	   // Эффект один и тот же.
	clq._ptr = reinterpret_cast<void*>(5);
	SetCls(clq);							   // Эффект один и тот же.
}
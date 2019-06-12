#pragma once // ≈сли убрать, то будет возможность включить этот заголовок более одного раза. “аким образом, будет ошибка компил€ции.
inline void CallMe()
{
	
}

class StaticVar
{
public:
	inline static int StaticInt; // ≈сли inline, то это ‘»«»„≈— » одна и та же перемена€ во всех единицах трансл€ции. ≈сли (), то это должна быть функци€, ќЅя«ј“≈Ћ№Ќќ определЄнна€ тут же. Ёта переменна€ будет автоматически »Ќ»÷»јЋ»«»–ќ¬јЌј.
	//static int MyStaticVariableOld; LNK
	static constexpr int MyStaticConstConstexpr = 44; // явл€етс€ константой.
};

//inline int StaticVar::MyStaticVariableOld = 0; // inline надо убрать.
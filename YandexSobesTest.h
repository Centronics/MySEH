#pragma once
#include <vector>
#include <chrono>
#include <deque>
#include <optional>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <set>

using namespace std;
using namespace std::chrono;

class A
{

};

class B
{

};

class Foo {  // NOLINT(hicpp-special-member-functions)
public:
	Foo(A* a, B* b) : a_(a), b_(b) {}

	Foo(const Foo& foo) : a_(nullptr), b_(nullptr)
	{
		try
		{
			if (foo.a_ != nullptr)
				a_ = new A(*foo.a_);

			if (foo.b_ != nullptr)
				b_ = new B(*foo.b_);
		}
		catch (...)
		{
			delete a_;
			delete b_;
			throw;
		}
	}

	~Foo() {
		delete a_;
		delete b_;
	}

	// Write the copy constructor for the class Foo. 
	// Ownership of a and b should be maintained by Foo.
	// Types A and B are copy-constructible.

private:
	A* a_;
	B* b_;
};

///////////////////////////////////////////////////////////////////////////////////////////

// 0 0 0 0 0 0 1 1 1 1 1 1 1
//           0 0 0 0 0 0 1 0 1 0 1 0 1
//           0 0 0 0 0 0 0 0 1 0 1 0 1
//           1 1 1 1 1 1 1 1 1 1 1 1 1
// 1 1 1 1 1 1 1 1 1 1 1 1 1

//  0 0 0 0 0 0 0 2 2 2 2 2


// 1 1 1 1

// 1 1 1 1 1 1 1 

inline bool VectorCompare(const vector<int>& v1, const vector<int>& v2)
{
	if (v1.size() != v2.size())
		return false;
	for (vector<int>::size_type k = 0; k < v1.size(); ++k)
		if (v1[k] != v2[k])
			return false;
	return true;
}

inline bool VerifyResult(const vector<int>& v)
{
	for (const int k : v)
		if (k == 0)
			return false;
	return true;
}

inline size_t OnesCount(const vector<int>& v)
{
	size_t r = 0;
	for (const auto k : v)
		r += k != 0;
	return r;
}

class VectorGenerator
{
public:

	class Iterator
	{
		VectorGenerator* _this = nullptr;

	public:
		Iterator() = default;

		Iterator(VectorGenerator* cur) : _this(cur)
		{
			if (_this->_signVector.empty())
				_this = nullptr;
		}

		[[nodiscard]] const vector<int>& operator*() const
		{
			return _this->_signVector;
		}

		Iterator& operator++()
		{
			_this->Generate();
			if (_this->_signVector.empty())
				_this = nullptr;
			return *this;
		}

		[[nodiscard]] bool operator!=(const Iterator& iterator) const
		{
			return _this != iterator._this;
		}
	};

	VectorGenerator(const size_t masLen) : _signVector(masLen) { }

private:
	vector<int> _signVector;

	void Generate()
	{
		vector<int>::size_type k = _signVector.size();
		while (k--)
			if (int* t = &_signVector[k]; *t == 0)
			{
				*t = 1;
				int* lastElement = &_signVector[0] + _signVector.size();
				if (int* t1 = t + 1; t1 < lastElement)
					memset(t1, 0, (lastElement - t1) * sizeof(int));
				return;
			}
		_signVector.clear();
	}

public:
	// ReSharper disable once CppInconsistentNaming
	[[nodiscard]] Iterator begin()
	{
		return Iterator(this);
	}

	// ReSharper disable once CppMemberFunctionMayBeStatic
	// ReSharper disable once CppInconsistentNaming
	[[nodiscard]] Iterator end()
	{
		return Iterator();
	}
};

struct Result
{
	tuple<long long, vector<int>> NonOpt;
	tuple<long long, vector<int>> Sobes;
};

inline Result RemoveZero(const vector<int>& mainVector)
{
	//for (vector<int>::size_type k = v.size() - 1; k >= 0; --k) // Œ–»√»Õ¿À
	//{
	//	if (v[k] == 1)
	//	{
	//		v[k] = 0;
	//		for (vector<int>::size_type i = 0; i < v.size(); ++i)
	//		{
	//			if (v[i] == 0)
	//			{
	//				v[i] = 1;
	//				break;
	//			}
	//		}
	//	}
	//}

	auto solNonOpt = [](vector<int> v) -> tuple<long long, vector<int>>
	{
		/*const auto getcomplexCount = [](const vector<int>& t) // Õ≈Œœ“»Ã¿À‹Õ€… ¿À√Œ–»“Ã, œ–»ƒ”Ã¿Õ ÃÕŒ… ƒÀﬂ “≈—“»–Œ¬¿Õ»ﬂ Œ—“¿À‹Õ€’
		{
			size_t elemsHandlingCount = 0;
			for (vector<int>::size_type k = 0; k < t.size(); ++k)
				if (t[k] == 0)
					elemsHandlingCount += t.size() - k;
				else
					++elemsHandlingCount;
			return elemsHandlingCount;
		};

		const size_t complexCount = getcomplexCount(v);
		size_t elemsHandlingCount = 0;*/
		//const steady_clock::time_point start = steady_clock::now();
		/*for (auto k = v.begin(); k != v.end(); )
		{
			if (*k == 0)
			{
				elemsHandlingCount += v.size() - (k - v.begin());
				k = v.erase(k);
				continue;
			}
			++k;
			++elemsHandlingCount;
		}*/
		//const steady_clock::time_point end = steady_clock::now();
		//if (elemsHandlingCount != complexCount)
			//throw;

		vector<int>::size_type lastZero = 0; // Œ“ÕŒ—»“≈À‹ÕŒ Œœ“»Ã¿À‹Õ€… ¿À√Œ–»“Ã, œ–»ƒ”Ã¿Õ ÃÕŒ… Õ¿ —Œ¡≈—≈ƒŒ¬¿Õ»» ¬ ﬂÕƒ≈ —≈
		bool needResize = false, needEnd = false;
		const vector<int>::size_type sz = v.size();
		vector<int>::size_type k = sz - 1;
		size_t elemsHandlingCount = 0;
		const steady_clock::time_point start = steady_clock::now();
		do
		{
			if (needResize && k == lastZero)
			{
				++elemsHandlingCount;
				if (v[k] != 0)
					++lastZero;
				needResize = true;
				break;
			}
			++elemsHandlingCount;
			if (v[k] == 0)
			{
				if (k != 0)
					continue;
				needResize = true;
				break;
			}
			vector<int>::size_type i = lastZero;
			for (; i < k; ++i)
			{
				++elemsHandlingCount;
				if (v[i] != 0)
					continue;
				v[i] = 1;
				v[k] = 0;
				lastZero = i + 1;
				needResize = true;
				if (k == lastZero)
					needEnd = true;
				break;
			}
			if (i == k)
			{
				lastZero = i + 1;
				needResize = true;
				break;
			}
		} while (!needEnd && k--);
		if (needResize)
			v.resize(lastZero);
		const steady_clock::time_point end = steady_clock::now();
		if (elemsHandlingCount != sz)
			throw;
		return make_tuple(duration_cast<nanoseconds>(end - start).count(), move(v));

		//return make_tuple(duration_cast<nanoseconds>(end - start).count(), move(v));
	};

	auto solSobes = [](vector<int> v) -> tuple<long long, vector<int>>
	{
		const steady_clock::time_point start = steady_clock::now(); // »« »Õ“≈–Õ≈“¿, —¿Ã€… Œœ“»Ã¿À‹Õ€…
		auto pStr = v.begin();
		auto str = v.cbegin();
		while (str != v.cend())
		{
			if (*str != 0)
			{
				*pStr = *str;
				++pStr;
			}
			++str;
		}
		v.resize(pStr - v.begin());
		const steady_clock::time_point end = steady_clock::now();
		return make_tuple(duration_cast<nanoseconds>(end - start).count(), move(v));
	};

	auto nonOpt = solNonOpt(mainVector);
	auto sobes = solSobes(mainVector);

	if (!VerifyResult(get<1>(nonOpt)) || !VerifyResult(get<1>(sobes)))
		throw;

	if (!VectorCompare(get<1>(nonOpt), get<1>(sobes)))
		throw;

	if (OnesCount(mainVector) != OnesCount(get<1>(sobes)))
		throw;

	return Result{ move(nonOpt),move(sobes) };
}

inline void RemoveTest(const size_t masLen, const bool writeToFile, ofstream& out)
{
	const auto getVectorSize = [masLen]
	{
		size_t result = 1;
		for (size_t k = 0; k < masLen; ++k)
			result <<= 1;
		return result;
	};

	const auto writeVectorToFile = [&out, writeToFile](const vector<int>& v)
	{
		if (!writeToFile)
			return;
		if (v.empty())
			out << "<empty> ";
		else
			for (const auto i : v)
			{
				out << i;
				out << " ";
			}
	};

	const auto writeResultToFile = [&out, writeToFile, &writeVectorToFile](const tuple<long long, vector<int>>& result, const char* comment)
	{
		if (!writeToFile)
			return;
		out << "=> " << comment << " = ";
		writeVectorToFile(get<1>(result));
		out << "=> Time = " << get<0>(result) << "ns" << endl;
	};

	bool makeMargin = false;
	vector<Result> d;
	d.reserve(getVectorSize());

	for (const vector<int>& v : VectorGenerator(masLen))
	{
		if (writeToFile)
			out << "Source = ";
		writeVectorToFile(v);
		if (writeToFile)
			out << endl;
		Result result = RemoveZero(v);
		writeResultToFile(result.Sobes, "Sobes");
		writeResultToFile(result.NonOpt, "NonOpt");
		if (writeToFile)
		{
			out << "--------------------------------------------------------------" << endl;
			makeMargin = true;
		}
		d.emplace_back(move(result));
	}

	if (writeToFile && makeMargin)
		out << endl;

	long long maxSobesAtts = 0, maxNonOptAtts = 0;
	long long timeSobesMax = 0, timeNonOptMax = 0;
	long long timeSobesOve = 0, timeNonOptOve = 0;
	long long timeSobesMin = LLONG_MAX, timeNonOptMin = LLONG_MAX;

	for (const auto& v : d)
	{
		{
			const long long t = get<0>(v.Sobes);
			timeSobesOve += t;
			if (timeSobesMax < t)
				timeSobesMax = t;
			if (timeSobesMin > t)
				timeSobesMin = t;
			++maxSobesAtts;
		}
		{
			const long long t = get<0>(v.NonOpt);
			timeNonOptOve += t;
			if (timeNonOptMax < t)
				timeNonOptMax = t;
			if (timeNonOptMin > t)
				timeNonOptMin = t;
			++maxNonOptAtts;
		}
	}

	if (writeToFile)
	{
		out << "<<< START OF TEST >>>" << endl;
		if (maxSobesAtts > 0)
		{
			out << "Attempts \"Sobes\" = " << maxSobesAtts << endl;
			out << "Max time \"Sobes\" = " << timeSobesMax << "ns" << endl;
			out << "Mid time \"Sobes\" = " << timeSobesOve / maxSobesAtts << "ns" << endl;
			out << "Min time \"Sobes\" = " << timeSobesMin << "ns" << endl;
		}
		else
			out << "<empty>" << endl;
		out << "--------------------------------------------------------------" << endl;
		if (maxNonOptAtts > 0)
		{
			out << "Attempts \"NonOpt\" = " << maxNonOptAtts << endl;
			out << "Max time \"NonOpt\" = " << timeNonOptMax << "ns" << endl;
			out << "Mid time \"NonOpt\" = " << timeNonOptOve / maxNonOptAtts << "ns" << endl;
			out << "Min time \"NonOpt\" = " << timeNonOptMin << "ns" << endl;
		}
		else
			out << "<empty>" << endl;
		out << "<<< END OF TEST >>>";
	}

	cout << "<<< START OF TEST >>>" << endl;
	if (maxSobesAtts > 0)
	{
		cout << "Attempts \"Sobes\" = " << maxSobesAtts << endl;
		cout << "Max time \"Sobes\" = " << timeSobesMax << "ns" << endl;
		cout << "Mid time \"Sobes\" = " << timeSobesOve / maxSobesAtts << "ns" << endl;
		cout << "Min time \"Sobes\" = " << timeSobesMin << "ns" << endl;
	}
	else
		cout << "<empty>" << endl;
	cout << "--------------------------------------------------------------" << endl;
	if (maxNonOptAtts > 0)
	{
		cout << "Attempts \"NonOpt\" = " << maxNonOptAtts << endl;
		cout << "Max time \"NonOpt\" = " << timeNonOptMax << "ns" << endl;
		cout << "Mid time \"NonOpt\" = " << timeNonOptOve / maxNonOptAtts << "ns" << endl;
		cout << "Min time \"NonOpt\" = " << timeNonOptMin << "ns" << endl;
	}
	else
		cout << "<empty>" << endl;
	cout << "<<< END OF TEST >>>" << endl << endl;
}

inline void ReverseLinkedList(list<int>&& lst)
{
	//	lst.reverse(); // –Â¯ÂÌËÂ

	struct Element
	{
		Element* Next = nullptr;
		int Value = 0;
	};

	class ForwardList
	{
		Element* _elt = nullptr;
		size_t _count = 0;

		[[nodiscard]] Element* GetElement(size_t n) const
		{
			if (_elt == nullptr)
				return nullptr;
			Element* e = _elt;
			do
			{
				if (n == 0)
					return e;
				n--;
				if (e->Next == nullptr)
					return nullptr;
				e = e->Next;
			} while (true);
		}

	public:

		void Add(const int& value)
		{
			if (_elt == nullptr)
			{
				_elt = new Element;
				_elt->Value = value;
				_count++;
				return;
			}
			Element* e = _elt;
			do
			{
				if (e->Next == nullptr)
				{
					e->Next = new Element{ nullptr, value };
					_count++;
					return;
				}
				e = e->Next;
			} while (true);
		}

		void Invert() const
		{
			if (_count == 0 || _count == 1)
				return;
			const size_t max = _count / 2;
			for (size_t k = _count - 1, j = 0; j < max; --k, ++j)
			{
				Element* eEnd = GetElement(k);
				Element* eBegin = GetElement(j);
				int bValue = move(eBegin->Value); // œÂÂÏÂ˘ÂÌËÂ
				eBegin->Value = move(eEnd->Value);
				eEnd->Value = move(bValue);
			}
		}
	};

	ForwardList fw;
	fw.Add(1);
	fw.Add(2);
	fw.Add(3);
	fw.Add(4);
	fw.Add(5);

	fw.Invert();
}

inline void ReadStringAB()
{
	string s;
	ifstream file("D:\\PriceList.dat");

	getline(file, s);

	file.close();

	char *a = &s[0], *pa = nullptr;
	const long long va = _strtoi64(a, &pa, 10);
	char* t;
	char *b = strtok_s(pa, " ", &t), *pb = nullptr;
	if (b == nullptr)
	{
		cout << "BAD1";
		return;
	}
	const long long vb = _strtoi64(b, &pb, 10);
	if (t != pb || pb != &s[s.size()])
	{
		cout << "BAD3";
		return;
	}

	/*long long va, vb;

	ifstream s("D:\\PriceList.dat");
	if (!s.is_open())
	{
		cout << "BAD4";
		return;
	}

	s >> va;
	s >> vb;*/

	if (va < -2'000'000'000 || va > 2'000'000'000)
	{
		cout << "BAD5";
		return;
	}
	if (vb < -2'000'000'000 || vb > 2'000'000'000)
	{
		cout << "BAD6";
		return;
	}
	cout << va + vb << endl;
}

inline int ReadBinaryString(const vector<bool>& v)
{
	int max = 0, cur = 0;
	for (vector<bool>::size_type k = 0; k < v.size(); ++k)
	{
		if (v[k])
		{
			++cur;
			if (cur > max)
				max = cur;
		}
		else
			cur = 0;
	}
	return max;
}

inline void RemoveCopies(vector<int>&& v)
{
	class mya
	{
	public:
		int n = 11;

		bool operator != (const mya&) const { return true; }
		mya operator *()const { return *this; }
		mya& get() { return *this; }

		/*—‡‚ÌÂÌËÂ (a!=b);
–‡Á˚ÏÂÌÓ‚‡ÌËÂ (*a);
»ÌÍÂÏÂÌÚ (a++ Ë ++a);
»ÌÍÂÏÂÌÚ ÁÌ‡˜ÂÌËˇ (*a++);*/
	};

	mya mm;
	mya& fg = mm.get();

	//set<mya> ma = {mya(), mya()};


	set<int> s = { 9,11,8,7,6,5,4,3,2,1,0 };//Ó‰ÌÓ ËÁ Â¯ÂÌËÈ
	set<int>::size_type n = s.count(1);
	set<int>::iterator e = s.find(10);
	set<int>::iterator f = s.find(11);
	s.erase(9);
	s.erase(f);
	//int g = *e; // AV

	for (vector<int>::size_type k = 0; k < v.size(); ++k)
	{
		//ÎË·Ó map, ÎË·Ó for
	}
}

inline vector<int> TwoSum(vector<int>&& nums, const int target)
{
	for (vector<int>::size_type i = 0; i < nums.size(); ++i)
		for (vector<int>::size_type j = 0; j < nums.size(); ++j)
			if (j != i && nums[i] + nums[j] == target)
				return vector<int>({ nums[i], nums[j] });
	return vector<int>();
}

inline int NonPairLinear(const vector<int>& v)
{
	const auto search = [&v](const int value)
	{
		int count = 0;
		for (const int j : v)
			count += j == value;
		return count == 2;
	};

	for (const int k : v)
		if (!search(k))
			return k;
	return -1;
	// return v.reduce(sum,val)=>sum^val,0); // “Œ∆≈ –≈ÿ≈Õ»≈
}

inline void YandexTest(const bool writeToFile)
{
	{
		A* pa = new A();
		B* pb = new B();
		const Foo f(pa, pb);
		// ReSharper disable once CppDeclaratorNeverUsed
		const Foo d(f);  // NOLINT(performance-unnecessary-copy-initialization)
		//_asm int 3;
	}

	{
		int len = ReadBinaryString({ true, true, true, true, true, true, true, true, false, true, true, true, true });

		auto twoSum = TwoSum({ 6,7,6,5 }, 6);

		RemoveCopies({ 0,1,2,3,4,5,6,7,8,9,9,7,6,5,4,3,2 });
	}

	{
		vector<int> vec;

		for (;;)
		{
			cout << "Input number:" << endl;
			int t;
			cin >> t;
			if (t < 0)
				break;
			vec.emplace_back(t);
		}

		if (const int result = NonPairLinear(vec); result < 0)
			cout << "Nonpair numbers is absent." << endl;
		else
			cout << "Nonpair number is: " << result << endl;
	}

	ofstream out;

	if (writeToFile)
	{
		out.open("D:\\Output.txt", ofstream::trunc);
		if (!out.is_open())
			throw;
	}

	for (size_t k = 60, max = 61; k < max; ++k)
	{
		RemoveTest(k, writeToFile, out);
		if (writeToFile && k < max - 1)
			out << endl << endl;
	}
}

/*Singleton* Singleton::Get()
 * {
 *		if(instance.load() == nullptr)
 *		{
 *			std::lock_gard<std::mutex> guard(lock);
 *			if(instance.load() == nullptr)
 *			{
 *				instance.store( Singleton());
 *			}
 *		}
 *		return instance.load();
 * }
 */
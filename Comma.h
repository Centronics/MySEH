#pragma once

class Mylogger
{
public:

	template <typename T> Mylogger & operator,(const T & val)
	{
		std::cout << val;
		return *this;
	}
};

inline void CommaDemo()
{
	Mylogger logv;
	auto t = (logv, 2, ":");

	vector<int> v;
	v.push_back((1, 2, 3, 4, 5, 6, 7, 8, 9));

	bool a = false;
	int i = (1, 5);

	int df = a && i++;

	i = (i, ++i, 1) + 1; // определено
	i = (++i, i++, i);     //  определено
	int j = i;
	j = (++i, i++, j*i); // определено 
}
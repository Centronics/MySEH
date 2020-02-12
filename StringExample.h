#pragma once
#include <iostream>
#include <winnt.h>

using namespace std;

inline void StringExample()
{
	// ASCII smiling face
	const char*     s1 = ":-)";

	// UTF-16 (on Windows) encoded WINKING FACE (U+1F609)
	const wchar_t*  s2 = L"😉 = \U0001F609 is ;-)";

	const char32_t* s10 = U"\U0001F609";

	const char* str2 = u8"\U0001F607 is O:-)";

	// UTF-8  encoded SMILING FACE WITH HALO (U+1F607)
	const char*     s3 = u8"😇 = \U0001F607 is O:-)";

	// UTF-16 encoded SMILING FACE WITH OPEN MOUTH (U+1F603)
	const char16_t* s4 = u"😃 = \U0001F603 is :-D";

	// UTF-32 encoded SMILING FACE WITH SUNGLASSES (U+1F60E)
	const char32_t* s5 = U"😎 = \U0001F60E is B-)";

	cout.seekp(0, ios_base::end);
	auto len = cout.tellp();
	{
		const string input = "abc abcd 123 1234 12356788 9876";
		size_t count = 0;
		for (string::size_type k = 0; k < input.size(); ++k)
		{
			const auto pos = input.find_first_of(' ', k);
			if (pos == string::npos)
			{
				count += ((input.size() - k) == 4);
				break;
			}
			count += (pos - k) == 4;
			k = pos;
		}

		UNREFERENCED_PARAMETER(count);
	}
}
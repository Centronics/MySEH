#pragma once
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <mutex>

using namespace std;

/*
 * Особенности:
 * 1) Приём в конструкторе значения вместо ссылки.
 * 2) Лучше принимать константную ссылку "const vector<string>&".
 * 3) В методе "AddFiles" мьютекс не освобождается в случае исключения. Лучше использовать lock_guard<mutex>. В методе "GetFilesImpl" то же самое.
 * 4) Метод "AddFiles" я переделал, т.к. очень подозрительной показалась конструкция обработки исключения, которая, мало того, что не выбрасывала исключения "наверх",
 * так она ещё и могла удалить "нормально" добавленный файл в случае возникновения исключения, причём, если оно возникает в функции push_back, то элемент добавлен не будет.
 * Рекомендуется использовать итераторы вместо индексации, т.к. доступ к элементам с их попомщью производится быстрее, чем с помощью индексации.
 * 5) В методе "GetFilesImpl" добавил проверку длины строки и убрал генерацию новой строки посредством "substr", т.к. это уменьшает быстродействие. Уменьшаю счётчик в случае удаления элемента массива.
 */

class EmergedGeneratedFilesObserver
{
public:
	EmergedGeneratedFilesObserver(const vector<string>& f)
	{
		AddFiles(f);
	}

	void AddFiles(const vector<string>& f)
	{
		const lock_guard<mutex> lock(m_mutex);
		for (auto it = f.cbegin(); it != f.cend(); ++it)
			m_files.push_back(*it);
	}

	vector<string> GetGarbageFiles()
	{
		return GetFilesImpl(Backup | Temp);
	}
	vector<string> GetRegularFiles()
	{
		return GetFilesImpl(Regular);
	}
	vector<string> GetAllFiles()
	{
		return GetFilesImpl(All);
	}

private:
	enum Flags : uint32_t // добавил тип
	{
		Temp = 1,
		Backup = 2,
		Regular = 4,
		All = 7
	};

	vector<string> GetFilesImpl(const uint32_t flags)
	{
		const lock_guard<mutex> lock(m_mutex);
		vector<string> v = m_files;

		for (vector<string>::size_type i = 0; i < v.size(); ++i)
		{
			if ((flags & Temp) == Temp && v[i].size() >= 4 && strcmp(v[i].c_str() + (v[i].size() - 4), ".tmp") == 0) // Проверку конца строки лучше вынести в отдельный метод, строки лучше убрать в ресурсы.
			{
				v.erase(v.begin() + i);
				if (i > 0)
					--i; // надо уменьшить на один шаг при удалении
			}
			if ((flags & Backup) == Backup && v[i].size() >= 4 && strcmp(v[i].c_str() + (v[i].size() - 4), ".bak") == 0)
			{
				v.erase(v.begin() + i);
				if (i > 0)
					--i; // надо уменьшить на один шаг при удалении
			}
			if ((flags & Regular) == Regular && v[i].size() >= 4 && (strcmp(v[i].c_str() + (v[i].size() - 4), ".bak") == 0 || strcmp(v[i].c_str() + (v[i].size() - 4), ".tmp") == 0))
			{
				v.erase(v.begin() + i);
				if (i > 0)
					--i; // надо уменьшить на один шаг при удалении
			}
		}

		return v;
	}

	mutex m_mutex;
	vector<string> m_files;
};

// Just a simple auto-test. Don't change its argument types and/or return types.
vector<int> solution(vector<string> &fileNames)
{
	EmergedGeneratedFilesObserver o({ "default.dat", "default.dat.tmp", "default.dat.bak" });

	for (const auto &fileName : fileNames)
	{
		o.AddFiles({ fileName, fileName + ".tmp", fileName + ".bak" });
	}

	const auto allFiles = o.GetAllFiles();
	const auto regularFiles = o.GetRegularFiles();
	const auto garbageFiles = o.GetGarbageFiles();

	//const auto PrintFiles = [](const vector<string>& files, const char* header)
	//{
	//    cout << header << ": " << endl;
	//    for (auto f : files)
	//        cout << "\t" << f << endl;
	//    cout << endl;
	//};

	//PrintFiles(allFiles, "All files");
	//PrintFiles(regularFiles, "Regular files");
	//PrintFiles(garbageFiles, "Garbage files");

	return {
		static_cast<int>(allFiles.size()),
		static_cast<int>(regularFiles.size()),
		static_cast<int>(garbageFiles.size())
	};
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ОРИГИНАЛ
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//#pragma once
//#include <sstream>
//#include <iostream>
//#include <vector>
//#include <string>
//#include <mutex>
//
//using namespace std;
//
///*
// * Особенности:
// * 1) Приём в конструкторе значения вместо ссылки.
// * 2) Лучше принимать константную ссылку "const vector<string>&".
// * 3) В методе "AddFiles" мьютекс не освобождается в случае исключения. Лучше использовать lock_guard<mutex>. В методе "GetFilesImpl" то же самое.
// * 4) Метод "AddFiles" я переделал, т.к. очень подозрительной показалась конструкция обработки исключения, которая, мало того, что не выбрасывала исключения "наверх",
// * так она ещё и могла удалить "нормально" добавленный файл в случае возникновения исключения, причём, если оно возникает в функции push_back, то элемент добавлен не будет.
// * Рекомендуется использовать итераторы вместо индексации, т.к. доступ к элементам с их попомщью производится быстрее, чем с помощью индексации.
// * 5) В методе "GetFilesImpl" добавил проверку длины строки и убрал генерацию новой строки посредством "substr", т.к. это уменьшает быстродействие. Уменьшаю счётчик в случае удаления элемента массива.
// */
//
//class EmergedGeneratedFilesObserver
//{
//public:
//	EmergedGeneratedFilesObserver(const vector<string>& f)
//	{
//		AddFiles(f);
//	}
//
//	void AddFiles(const vector<string>& f)
//	{
//		try
//		{
//			const lock_guard<mutex> lock(m_mutex);
//			for (auto it = f.cbegin(); it != f.cend(); ++it)
//				m_files.push_back(*it);
//		}
//		catch (...)
//		{
//			throw;
//		}
//	}
//
//	vector<string> GetGarbageFiles()
//	{
//		return GetFilesImpl(Backup | Temp);
//	}
//	vector<string> GetRegularFiles()
//	{
//		return GetFilesImpl(Regular);
//	}
//	vector<string> GetAllFiles()
//	{
//		return GetFilesImpl(All);
//	}
//
//private:
//	enum Flags : uint32_t // добавил тип
//	{
//		Temp = 1,
//		Backup = 2,
//		Regular = 4,
//		All = 7
//	};
//
//	vector<string> GetFilesImpl(const uint32_t flags)
//	{
//		const lock_guard<mutex> lock(m_mutex);
//		vector<string> v = m_files;
//
//		for (vector<string>::size_type i = 0; i < v.size(); ++i)
//		{
//			if ((flags == Temp) && v[i].size() >= 4 && strcmp(v[i].c_str() + v[i].size() - 4, ".tmp") == 0)
//			{
//				v.erase(v.begin() + i);
//				if (i > 0)
//					--i; // надо уменьшить на один шаг при удалении
//			}
//			if ((flags == Backup) && v[i].size() >= 4 && strcmp(v[i].c_str() + v[i].size() - 4, ".bak") == 0)
//			{
//				v.erase(v.begin() + i);
//				if (i > 0)
//					--i; // надо уменьшить на один шаг при удалении
//			}
//			if ((flags == Regular) && v[i].size() >= 4 && strcmp(v[i].c_str() + v[i].size() - 4, ".bak") != 0 && strcmp(v[i].c_str() + v[i].size() - 4, ".tmp") != 0)
//			{
//				v.erase(v.begin() + i);
//				if (i > 0)
//					--i; // надо уменьшить на один шаг при удалении
//			}
//		}
//
//		return v;
//	}
//
//	mutex m_mutex;
//	vector<string> m_files;
//};
//
//// Just a simple auto-test. Don't change its argument types and/or return types.
//vector<int> solution(vector<string> &fileNames)
//{
//	EmergedGeneratedFilesObserver o({ "default.dat", "default.dat.tmp", "default.dat.bak" });
//
//	for (const auto &fileName : fileNames)
//	{
//		o.AddFiles({ fileName, fileName + ".tmp", fileName + ".bak" });
//	}
//
//	const auto allFiles = o.GetAllFiles();
//	const auto regularFiles = o.GetRegularFiles();
//	const auto garbageFiles = o.GetGarbageFiles();
//
//	//const auto PrintFiles = [](const vector<string>& files, const char* header)
//	//{
//	//    cout << header << ": " << endl;
//	//    for (auto f : files)
//	//        cout << "\t" << f << endl;
//	//    cout << endl;
//	//};
//
//	//PrintFiles(allFiles, "All files");
//	//PrintFiles(regularFiles, "Regular files");
//	//PrintFiles(garbageFiles, "Garbage files");
//
//	return {
//		static_cast<int>(allFiles.size()),
//		static_cast<int>(regularFiles.size()),
//		static_cast<int>(garbageFiles.size())
//	};
//}

#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <atomic>
#include <thread>
#include <stack>
#include <mutex>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

// ÇÀÄÀ×À ¹1.
inline void FileReader()
{
	ifstream file(L"D:\\file.txt");
	if (!file)
		return;
	map<string, unsigned> mp;
	while (!file.eof())
	{
		string str;
		file >> str;
		if (str.empty())
			continue;
		++mp[str];
	}
	file.close();
	multimap<unsigned, string> mm;
	for (pair<string, unsigned> p : mp)
		mm.insert(pair<unsigned, string>(p.second, p.first));
	for (auto k = mm.crbegin(); k != mm.crend(); ++k)
		cout << k->second << ' ' << k->first << " times" << endl;
}

// ÇÀÄÀ×À ¹4.

class LogWriter
{
	stack<string> _strings;
	mutex _mutex, _thrMutex;
	condition_variable _event;
	bool _needStop = false, _notified = false;
	thread _workThread;

public:

	LogWriter() : _workThread([this]() mutable -> void
	{
		try
		{
			ofstream file("D:\\LOG.txt", ofstream::trunc);
			unique_lock<mutex> varLock(_thrMutex);
			while (!_needStop)
			{
				bool isEmpty;
				{
					const lock_guard<mutex> lock(_mutex);
					isEmpty = _strings.empty();
				}
				if (!isEmpty)
				{
					string t;
					{
						const lock_guard<mutex> lock(_mutex);
						_notified = false;
						t = _strings.top();
						_strings.pop();
					}
					file << t;
					if (_needStop)
						return;
				}
				while (!_notified)
					_event.wait(varLock);
			}
		}
		catch (...)
		{

		}
	}) {	}

	LogWriter(const LogWriter&) = delete;
	LogWriter(LogWriter&&) = delete;
	LogWriter& operator=(const LogWriter&) = delete;
	LogWriter& operator=(LogWriter&&) = delete;

	void WriteString(const string& str)
	{
		const unique_lock<mutex> varLock(_thrMutex);
		{
			const lock_guard<mutex> lock(_mutex);
			_strings.push(str);
		}
		_notified = true;
		_event.notify_all();
	}

	~LogWriter()
	{
		_needStop = true;
		_workThread.join();
	}
};

inline void Multithreading()
{
	unique_ptr<LogWriter> logWriter(new LogWriter);
	vector<thread> thrs;
	static atomic<unsigned> number = 0;
	volatile bool finish = false;
	for (int k = 0; k < 20; ++k)
		thrs.emplace_back(thread([&logWriter, &finish]
	{
		const unsigned myNumber = number++;
		srand(static_cast<unsigned>(time(NULL)));
		while (!finish)
		{
			const time_t now = time(0);
			logWriter->WriteString("Thread #" + to_string(myNumber) + ' ' + ctime(&now));
			this_thread::sleep_for(milliseconds(500 + (rand() % 5000)));
		}
	}));
	this_thread::sleep_for(seconds(30));
	finish = true;
	for (auto& t : thrs)
		t.join();
}
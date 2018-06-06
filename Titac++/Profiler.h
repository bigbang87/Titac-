#pragma once
#include <string>
#include <map>
#include <iostream>
#include <chrono>
#include <functional>
#include <optional>

using namespace std;
typedef chrono::high_resolution_clock clock;
typedef chrono::steady_clock::time_point timer_point;
typedef chrono::duration<double> duration;

class Profiler
{
public:
	static void startTimer(string timerName)
	{
		size_t str_hash = hash<string>{}(timerName);
		map<timer_point, size_t>::iterator map_it = timersMap.begin();


		timersMap.insert(map_it, pair<timer_point, size_t>(clock::now(), 0));
	}

	static void endTimer(string timerName)
	{
		size_t str_hash = hash<string>{}(timerName);
		timer_point end = clock::now();
		//duration timerDuration = map_it->first - end;
	}

	static optional<timer_point> getTimer(size_t str_hash)
	{
		map<timer_point, size_t>::iterator map_it;
		for (map_it = timersMap.begin(); map_it != timersMap.end(); ++map_it)
		{
			//if (map_it->second == str_hash)
				//return std::optional<timer_point>{map_it->first};
		}
		timer_point a = clock::now();
		optional<timer_point> b = a;
		return {};
	}

private:
	static map<timer_point, size_t> timersMap;
};
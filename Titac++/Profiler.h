#pragma once
#include <string>
#include <map>
#include <iostream>
#include <chrono>

using namespace std;
typedef chrono::high_resolution_clock clock;
typedef chrono::steady_clock::time_point timer_point;
typedef chrono::duration<double> duration;

class Profiler
{
public:
	static void startTimer(string timerName)
	{
		map<string, timer_point>::iterator map_it = timersMap.find(timerName);
		if (map_it != timersMap.end())
			return;
		map_it = timersMap.begin();
		timersMap.insert(map_it, pair<string, timer_point>(timerName, clock::now()));
	}

	static void endTimer(string timerName)
	{
		map<string, timer_point>::iterator map_it = timersMap.find(timerName);
		if (map_it == timersMap.end())
			return;
		timer_point end = clock::now();
		duration dur = end - map_it->second;
		timersMap.erase(map_it);
	}

private:
	static map<string, timer_point> timersMap;
};
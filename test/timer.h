#pragma once

#if _MSC_VER
#include <Windows.h>
#elif __GNUC__
#include <ctime>
#include <chrono>
using namespace std::chrono;
#endif

using namespace std;

#if _MSC_VER
struct Timer { // High performance Win64 timer using QPC events
	double PCFreq = 0.0;
	double elapsed_time_milliseconds = 0.0;
	LARGE_INTEGER start_time;
	LARGE_INTEGER end_time;

	inline Timer() {
		LARGE_INTEGER li;
		QueryPerformanceFrequency(&li);
		PCFreq = double(li.QuadPart) / 1000.0;
	}

	inline void reset() {
		elapsed_time_milliseconds = 0.0;
	}

	inline void start() {
		QueryPerformanceCounter(&start_time);
	}

	inline void stop() {
		QueryPerformanceCounter(&end_time);
		elapsed_time_milliseconds += double((end_time.QuadPart - start_time.QuadPart) / PCFreq);
	}
};
#elif __GNUC__
struct Timer { // High perofrmance timer using standard c++11 chrono
	double elapsed_time_milliseconds = 0;
	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;

	inline Timer() {

	}

	inline void start() {
		t1 = high_resolution_clock::now();
	}

	inline void stop() {
		t2 = high_resolution_clock::now();
		elapsed_time_milliseconds += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	}
};
#endif
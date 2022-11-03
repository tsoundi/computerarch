#include <chrono> 

// this file is compiled with Od and intrinsics
//   override the compilation configuration for this file: right-click on file and choose Properties


using namespace std::chrono;

_int64 version_c_Od_Intrinsics(int n, float* arr, float* arr2, float* result) {
	time_point<system_clock> now = system_clock::now();

	for (int i = 0; i < n; ++i) {
		result[i] = arr[i] * arr2[i];
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}
#include <chrono> 

// this file is compiled with O2 and no intrinsics
// override the compilation configuration for this file: right-click on file and choose Properties

using namespace std::chrono;

_int64 version_c_O2_NoIntrinsics(int n, short* arr, short* arr2, short* result) {
	time_point<system_clock> now = system_clock::now();

#pragma loop(no_vector)	// by default the vectorization is on, with this we disable vectorization
	for (int i = 0; i < n; ++i) {
		result[i] = arr[i] * arr2[i];
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}


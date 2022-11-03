#include <chrono> 
#include <immintrin.h>
// this file is compiled with Od and no intrinsics
//   override the compilation configuration for this file: right-click on file and choose Properties


using namespace std::chrono;

_int64 version_c_Od_NoIntrinsics(int n, int* arr, int* arr2, int* result){
	time_point<system_clock> now = system_clock::now();


#pragma loop(no_vector)	
	for (int i = 0; i < n; ++i) {
		result[i] = arr[i] * arr2[i];
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}

_int64 version_c_Od_NoIntrinsics_nopragma(int n, int* arr, int* arr2, int* result) {
	time_point<system_clock> now = system_clock::now();



	for (int i = 0; i < n; ++i) {
		result[i] = arr[i] * arr2[i];
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}

_int64 version_Od_ManualLoopUnrolling(int n, int* arr, int* arr2, int* result) {
	time_point<system_clock> now = system_clock::now();

//#pragma loop(no_vector)
//	for (int i = 0; i < n; ++i) {
//		result[i] = arr[i] * arr2[i];
//		//	cout << arr[i] << ", ";
//	}
#pragma loop(no_vector)	
	for (int i = 0; i < n; i+=4) {
		result[i] = arr[i] * arr2[i];
		result[i+1] = arr[i+1] * arr2[i+1];
		result[i+2] = arr[i+2] * arr2[i+2];
		result[i+3] = arr[i+3] * arr2[i+3];
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}

_int64 version_Od_PragmaUnroll(int n, int* arr, int* arr2, int* result) {
	time_point<system_clock> now = system_clock::now();

	#pragma loop(no_vector)
	#pragma unroll
	for (int i = 0; i < n; ++i) {
		result[i] = arr[i] * arr2[i];
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}
_int64 version_Od_PragmaUnrollInner(int n, int* arr, int* arr2, int* result) {
	time_point<system_clock> now = system_clock::now();

	const int INNER = 4;
	#pragma loop(no_vector)
	for (int i = 0; i < n; i += INNER) {
		#pragma loop(no_vector)
		#pragma unroll
		for (int j = 0; j < INNER; j ++)
			result[i+j] = arr[i+j] * arr2[i+j];
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}

int product(int x1, int x2) {
	return x1 * x2;
}

_int64 version_Od_xFunction(int n, int* arr, int* arr2, int* result) {
	time_point<system_clock> now = system_clock::now();

#pragma loop(no_vector)
	for (int i = 0; i < n; ++i) {
		result[i] = product(arr[i], arr2[i]);
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}

inline int product2(int x1, int x2) {
	return x1 * x2;
}

_int64 version_Od_xFunction_inline(int n, int* arr, int* arr2, int* result) {
	time_point<system_clock> now = system_clock::now();

#pragma loop(no_vector)
	for (int i = 0; i < n; ++i) {
		result[i] = product2(arr[i], arr2[i]);
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}
_int64 version_loopUnrolling_8(int n, int* arr, int* arr2, int* result) {
	time_point<system_clock> now = system_clock::now();

	for (int i = 0; i < n; i += 8) {
		result[i] = arr[i] * arr2[i];
		result[i + 1] = arr[i + 1] * arr2[i + 1];
		result[i + 2] = arr[i + 2] * arr2[i + 2];
		result[i + 3] = arr[i + 3] * arr2[i + 3];
		result[i + 4] = arr[i + 4] * arr2[i + 4];
		result[i + 5] = arr[i + 5] * arr2[i + 5];
		result[i + 6] = arr[i + 6] * arr2[i + 6];
		result[i + 7] = arr[i + 7] * arr2[i + 7];
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}

_int64 version_loopUnrolling_16(int n, int* arr, int* arr2, int* result) {
	time_point<system_clock> now = system_clock::now();

	for (int i = 0; i < n; i += 16) {
		result[i] = arr[i] * arr2[i];
		result[i + 1] = arr[i + 1] * arr2[i + 1];
		result[i + 2] = arr[i + 2] * arr2[i + 2];
		result[i + 3] = arr[i + 3] * arr2[i + 3];
		result[i + 4] = arr[i + 4] * arr2[i + 4];
		result[i + 5] = arr[i + 5] * arr2[i + 5];
		result[i + 6] = arr[i + 6] * arr2[i + 6];
		result[i + 7] = arr[i + 7] * arr2[i + 7];
		result[i + 8] = arr[i + 8] * arr2[i + 8];
		result[i + 9] = arr[i + 9] * arr2[i + 9];
		result[i + 10] = arr[i + 10] * arr2[i + 10];
		result[i + 11] = arr[i + 11] * arr2[i + 11];
		result[i + 12] = arr[i + 12] * arr2[i + 12];
		result[i + 13] = arr[i + 13] * arr2[i + 13];
		result[i + 14] = arr[i + 14] * arr2[i + 14];
		result[i + 15] = arr[i + 15] * arr2[i + 15];
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}

_int64 version_loopUnrolling_32(int n, int* arr, int* arr2, int* result) {
	time_point<system_clock> now = system_clock::now();

	for (int i = 0; i < n; i += 32) {
		result[i] = arr[i] * arr2[i];
		result[i + 1] = arr[i + 1] * arr2[i + 1];
		result[i + 2] = arr[i + 2] * arr2[i + 2];
		result[i + 3] = arr[i + 3] * arr2[i + 3];
		result[i + 4] = arr[i + 4] * arr2[i + 4];
		result[i + 5] = arr[i + 5] * arr2[i + 5];
		result[i + 6] = arr[i + 6] * arr2[i + 6];
		result[i + 7] = arr[i + 7] * arr2[i + 7];
		result[i + 8] = arr[i + 8] * arr2[i + 8];
		result[i + 9] = arr[i + 9] * arr2[i + 9];
		result[i + 10] = arr[i + 10] * arr2[i + 10];
		result[i + 11] = arr[i + 11] * arr2[i + 11];
		result[i + 12] = arr[i + 12] * arr2[i + 12];
		result[i + 13] = arr[i + 13] * arr2[i + 13];
		result[i + 14] = arr[i + 14] * arr2[i + 14];
		result[i + 15] = arr[i + 15] * arr2[i + 15];
		result[i + 16] = arr[i + 16] * arr2[i + 16];
		result[i + 17] = arr[i + 17] * arr2[i + 17];
		result[i + 18] = arr[i + 18] * arr2[i + 18];
		result[i + 19] = arr[i + 19] * arr2[i + 19];
		result[i + 20] = arr[i + 20] * arr2[i + 20];
		result[i + 21] = arr[i + 21] * arr2[i + 21];
		result[i + 22] = arr[i + 22] * arr2[i + 22];
		result[i + 23] = arr[i + 23] * arr2[i + 23];
		result[i + 24] = arr[i + 24] * arr2[i + 24];
		result[i + 25] = arr[i + 25] * arr2[i + 25];
		result[i + 26] = arr[i + 26] * arr2[i + 26];
		result[i + 27] = arr[i + 27] * arr2[i + 27];
		result[i + 28] = arr[i + 28] * arr2[i + 28];
		result[i + 29] = arr[i + 29] * arr2[i + 29];
		result[i + 30] = arr[i + 30] * arr2[i + 30];
		result[i + 31] = arr[i + 31] * arr2[i + 31];
		
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}

_int64 version_vectorization(int n, int* arr, int* arr2, int* result) {
	time_point<system_clock> now = system_clock::now();
	for (int i = 0; i < n; i += 8) {
		__m256i vec1 = _mm256_load_si256((__m256i*) &arr[i]);
		__m256i vec2 = _mm256_load_si256((__m256i*) &arr2[i]);
		
		__m256i res = _mm256_mullo_epi32(vec1, vec2);
		
		//_mm256_store_si256((__m256i*) &result[i], res);

		
		result[i] = _mm256_extract_epi32(res, 0);
		result[i + 1] = _mm256_extract_epi32(res, 1);
		result[i + 2] = _mm256_extract_epi32(res, 2);
		result[i + 3] = _mm256_extract_epi32(res, 3);
		result[i + 4] = _mm256_extract_epi32(res, 4);
		result[i + 5] = _mm256_extract_epi32(res, 5);
		result[i + 6] = _mm256_extract_epi32(res, 6);
		result[i + 7] = _mm256_extract_epi32(res, 7);
		
		
		

	}
			time_point<system_clock> epoch = system_clock::now();
		microseconds us = duration_cast<microseconds>(epoch - now);

		return us.count();
	
}
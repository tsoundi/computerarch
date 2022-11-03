#include <chrono> 
#include <immintrin.h>
// this file is compiled with Od and no intrinsics
//   override the compilation configuration for this file: right-click on file and choose Properties


using namespace std::chrono;

_int64 version_c_Od_NoIntrinsics(int n, short* arr, short* arr2, short* result){
	time_point<system_clock> now = system_clock::now();


#pragma loop(no_vector)	
	for (int i = 0; i < n; ++i) {
		result[i] = arr[i] * arr2[i];
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}

_int64 version_c_Od_NoIntrinsics_nopragma(int n, short* arr, short* arr2, short* result) {
	time_point<system_clock> now = system_clock::now();



	for (int i = 0; i < n; ++i) {
		result[i] = arr[i] * arr2[i];
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}

_int64 version_Od_ManualLoopUnrolling(int n, short* arr, short* arr2, short* result) {
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

_int64 version_Od_PragmaUnroll(int n, short* arr, short* arr2, short* result) {
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
_int64 version_Od_PragmaUnrollInner(int n, short* arr, short* arr2, short* result) {
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

short product(short x1, short x2) {
	return x1 * x2;
}

_int64 version_Od_xFunction(int n, short* arr, short* arr2, short* result) {
	time_point<system_clock> now = system_clock::now();

#pragma loop(no_vector)
	for (int i = 0; i < n; ++i) {
		result[i] = product(arr[i], arr2[i]);
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}

inline short product2(short x1, short x2) {
	return x1 * x2;
}

_int64 version_Od_xFunction_inline(int n, short* arr, short* arr2, short* result) {
	time_point<system_clock> now = system_clock::now();

#pragma loop(no_vector)
	for (int i = 0; i < n; ++i) {
		result[i] = product2(arr[i], arr2[i]);
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}
_int64 version_loopUnrolling_8(int n, short* arr, short* arr2, short* result) {
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

_int64 version_loopUnrolling_16(int n, short* arr, short* arr2, short* result) {
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

_int64 version_loopUnrolling_32(int n, short* arr, short* arr2, short* result) {
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

_int64 version_vectorization(int n, short* arr, short* arr2, short* result) {
	time_point<system_clock> now = system_clock::now();
	for (int i = 0; i < n; i += 16) {
		__m256i vec1 = _mm256_load_si256((__m256i*) &arr[i]);
		__m256i vec2 = _mm256_load_si256((__m256i*) &arr2[i]);
		
		__m256i res = _mm256_mullo_epi16(vec1, vec2);
		
		_mm256_store_si256((__m256i*) &result[i], res);
	
	}
			time_point<system_clock> epoch = system_clock::now();
		microseconds us = duration_cast<microseconds>(epoch - now);

		return us.count();
	
}

_int64 version_vectorization_and_loopenrolling(int n, short* arr, short* arr2, short* result) {
	time_point<system_clock> now = system_clock::now();
	for (int i = 0; i < n; i += 64) {
		__m256i vec1 = _mm256_load_si256((__m256i*) & arr[i]);
		__m256i vec2 = _mm256_load_si256((__m256i*) & arr2[i]);

		__m256i res = _mm256_mullo_epi16(vec1, vec2);

		_mm256_store_si256((__m256i*) & result[i], res);

		//########################################################################################
		__m256i vec3 = _mm256_load_si256((__m256i*) & arr[i+16]);
		__m256i vec4 = _mm256_load_si256((__m256i*) & arr2[i+16]);

		__m256i res2 = _mm256_mullo_epi16(vec3, vec4);

		_mm256_store_si256((__m256i*) & result[i+16], res2);

		//########################################################################################
		__m256i vec5 = _mm256_load_si256((__m256i*) & arr[i + 32]);
		__m256i vec6 = _mm256_load_si256((__m256i*) & arr2[i + 32]);

		__m256i res3 = _mm256_mullo_epi16(vec5, vec6);

		_mm256_store_si256((__m256i*) & result[i + 32], res3);

		//########################################################################################
		__m256i vec7 = _mm256_load_si256((__m256i*) & arr[i + 48]);
		__m256i vec8 = _mm256_load_si256((__m256i*) & arr2[i + 48]);

		__m256i res4 = _mm256_mullo_epi16(vec7, vec8);

		_mm256_store_si256((__m256i*) & result[i + 48], res4);
	}
	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();

}
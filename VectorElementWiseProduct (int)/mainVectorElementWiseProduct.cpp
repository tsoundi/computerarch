#include <exception>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <random> 
#include <time.h>
#include <chrono>
#include <immintrin.h> // for vector instructions
#include <thread> // for multithreading
#include <omp.h>  //openmp

#include "versions_o2_nointrinsics.h"
#include "versions_od_intrinsics.h"
#include "versions_od_nointrinsics.h"

#include <windows.h> // for: LARGE_INTEGER, QueryPerformanceFrequency, SYSTEM_INFO
#pragma comment(lib, "user32.lib") // for retrieving CPU information

using namespace std;
using namespace std::chrono;

#define N 1024 * 1024 * 16 // size of the arrays
#define NBR_EXPERIMENTS 10 // all versions are tested multiple times and runtimes averaged
#define NBR_ALGORITHM_VERSIONS 100 // take big enough

// the different sequential versions (defined below)
_int64 sequential_version(const int n, int* arr, int* arr2, int* result);
_int64 version_constant_size(int n, int* arr, int* arr2, int* result);


_int64 version_PragmaUnrollInner(int n, int* arr, int* arr2, int* result);
_int64 version_loopUnrolling_8(int n, int* arr, int* arr2, int* result);
_int64 version_loopUnrolling_16(int n, int* arr, int* arr2, int* result);
_int64 version_loopUnrolling_32(int n, int* arr, int* arr2, int* result);
_int64 version_vectorization(int n, int* arr, int* arr2, int* result);
_int64 version_vectorization_and_loopenrolling(int n, int* arr, int* arr2, int* result);

// utility functions
void checkIfResultsAreTheSame(string name, int* arr3, int* arr4, int n);
_int64 minimalValue(_int64* values, int NBR);
_int64 meanValue(_int64* values, int NBR);
_int64 stddev(_int64* values, int NBR);

void analyzePerformance(vector<string> names, _int64 runtimes[NBR_ALGORITHM_VERSIONS][NBR_EXPERIMENTS], _int64 totalNbrOfOperations, _int64 totalNbrOfBytes, _int64 ticksPerMilliSecond, _int64 referenceTime);

bool PRINT_DATA = false; // set this to true to print input & output data. Use this to debug

int main(int argc, char *argv[])
{
	_int64 totalNbrOfOperations = N * 1;
	_int64 totalNbrOfBytes = N * 12;

	LARGE_INTEGER lpFrequency;
	bool ok = QueryPerformanceFrequency(&lpFrequency);
	_int64 ticksPerMilliSecond = lpFrequency.QuadPart; 

	cout << "** Comparison of element-wise product of 2 vectors ** " << endl;
	cout << "Vector size N = " << N << " Nbr Experiments = " << NBR_EXPERIMENTS << " PRINT_DATA = "<< PRINT_DATA<< " => " << totalNbrOfOperations << " operations and "<<totalNbrOfBytes <<" bytes transferred"<<endl;

	if (N % 16 != 0) {
		cout << "N (" << N << ") should be a multiple of 16 (for the multithreaded versions)!" << endl;
		return -1;
	}

	if (ok)
		cout <<"CPU frequency = " << (float)ticksPerMilliSecond / 1000000 << "GHz" ;
	else
		cout << "CPU frequency cannot be identified." ;

	//cout << "long = " << sizeof(long) << "B, _int64 = " << sizeof(_int64) <<"B"<< endl;

	// CPU information. 
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);
	int nbrCores = siSysInfo.dwNumberOfProcessors;
	cout << " " << nbrCores << " cores"<<endl;
	//if (N % nbrCores != 0) {
	//	cout << "N (" << N << ") should be a multiple of the number of cores "<< nbrCores<<" (for the multithreaded versions)!" << endl;
	//	return -1;
	//}

	printf("Hardware information: \n");
	printf("  OEM ID: %u\n", siSysInfo.dwOemId);
	printf("  Number of processors: %u\n",siSysInfo.dwNumberOfProcessors);
	//printf("  Page size: %u\n", siSysInfo.dwPageSize);
	//printf("  Processor type: %u\n", siSysInfo.dwProcessorType);
	//printf("  Minimum application address: %lx\n", siSysInfo.lpMinimumApplicationAddress);
	//printf("  Maximum application address: %lx\n",siSysInfo.lpMaximumApplicationAddress);
	//printf("  Active processor mask: %u\n", siSysInfo.dwActiveProcessorMask);

	cout <<  endl;

	srand(time(NULL)); // random initial seed

	// allocation and initialization
	int* arr = new int[N], *arr2 = new int[N]; // input array
	int* arr3 = new int[N]; // result of sequential version (the truth)
	int* arr4 = new int[N]; // results of the alternative versions (will be compared with the truth)
	for (int i = 0; i < N; i++) {
		arr[i] = rand();
		arr2[i] = rand();
		if (PRINT_DATA && i < 10) cout << arr[i] << "*" << arr2[i] << ", ";
		arr3[i] = 0; // actually, initialization is not necessary
		arr4[i] = 0;
	}
	if (PRINT_DATA) cout << endl;


	_int64 runtimes[NBR_ALGORITHM_VERSIONS][NBR_EXPERIMENTS];
	vector<string> names;
	
	for (int t = 0; t < NBR_EXPERIMENTS; t++) { // run multiple times because of fluctuations
		int version = 0;
		// ********* THE FIRST VERSION - THE REFERENCE *********
		runtimes[version++][t] = sequential_version(N, arr, arr2, arr3); // returns time in microseconds
		if (t==0) names.push_back( "Sequential version");

		// ********* THE SECOND VERSION *********
		runtimes[version++][t] = version_constant_size(N, arr, arr2, arr4); // returns time in microseconds
		if (t == 0) {
			names.push_back("C - size is constant N");
			checkIfResultsAreTheSame(names.back(), arr3, arr4, N);
		}

		// ********* ANOTHER VERSION *********
		runtimes[version++][t] = version_c_Od_NoIntrinsics(N, arr, arr2, arr4); // returns time in microseconds
		if (t == 0) {
			names.push_back("C - Od No Intrinsics");
			checkIfResultsAreTheSame(names.back(), arr3, arr4, N);
		}

		// ********* YET ANOTHER VERSION *********
		runtimes[version++][t] = version_c_O2_NoIntrinsics(N, arr, arr2, arr4); // returns time in microseconds
		if (t == 0) {
			names.push_back("C - O2 No Intrinsics");
			checkIfResultsAreTheSame(names.back(), arr3, arr4, N);
		}

	
		// ********* ADD VERSIONS HERE *********
		runtimes[version++][t] = version_PragmaUnrollInner(N, arr, arr2, arr4); // returns time in microseconds
		if (t == 0) {
			names.push_back("PragmaUnrollInner");
			checkIfResultsAreTheSame(names.back(), arr3, arr4, N);
		}

		runtimes[version++][t] = version_Od_ManualLoopUnrolling(N, arr, arr2, arr4); // returns time in microseconds
		if (t == 0) {
			names.push_back("ManualLoopUnrolling Od");
			checkIfResultsAreTheSame(names.back(), arr3, arr4, N);
		}

		runtimes[version++][t] = version_loopUnrolling_8(N, arr, arr2, arr4); // returns time in microseconds
		if (t == 0) {
			names.push_back("ManualLoopUnrolling_8");
			checkIfResultsAreTheSame(names.back(), arr3, arr4, N);
		}

		runtimes[version++][t] = version_loopUnrolling_16(N, arr, arr2, arr4); // returns time in microseconds
		if (t == 0) {
			names.push_back("ManualLoopUnrolling_16");
			checkIfResultsAreTheSame(names.back(), arr3, arr4, N);
		}

		runtimes[version++][t] = version_loopUnrolling_32(N, arr, arr2, arr4); // returns time in microseconds
		if (t == 0) {
			names.push_back("ManualLoopUnrolling_32");
			checkIfResultsAreTheSame(names.back(), arr3, arr4, N);
		}

		runtimes[version++][t] = version_vectorization(N, arr, arr2, arr4); // returns time in microseconds
		if (t == 0) {
			names.push_back("Vectorization");
			checkIfResultsAreTheSame(names.back(), arr3, arr4, N);
		}

		runtimes[version++][t] = version_vectorization_and_loopenrolling(N, arr, arr2, arr4); // returns time in microseconds
		if (t == 0) {
			names.push_back("Vectorization and manual LU");
			checkIfResultsAreTheSame(names.back(), arr3, arr4, N);
		}

		// ********* END OF ALL VERSIONS *********
	}
	_int64 referenceTime = minimalValue(runtimes[0], NBR_EXPERIMENTS);// FIRST algorithm
	analyzePerformance(names, runtimes, totalNbrOfOperations, totalNbrOfBytes, ticksPerMilliSecond, referenceTime);

	// Deallocate memory
	delete[] arr; delete[] arr2; delete[] arr3; delete[] arr4;

	cout << endl<<"Press ENTER to close window...";
	char c = cin.get();
}


//  ==== ALL VERSIONS ====
_int64 sequential_version(int n, int* arr, int* arr2, int* result) {
	time_point<system_clock> now = system_clock::now();

	for (int i = 0; i < n; ++i) {
		result[i] = arr[i] * arr2[i];
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}

_int64 version_constant_size(int n, int* arr, int* arr2, int* result) {
	time_point<system_clock> now = system_clock::now();

	for (int i = 0; i < N; ++i) {  // WE ARE USING THE CONSTANT N HERE, so compiler knows the number of iterations
		result[i] = arr[i] * arr2[i];
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}


_int64 version_PragmaUnrollInner(int n, int* arr, int* arr2, int* result) {
	time_point<system_clock> now = system_clock::now();

	const int INNER = 4;
#pragma loop(no_vector)
	for (int i = 0; i < n; i += INNER) {
#pragma loop(no_vector)
#pragma unroll
		for (int j = 0; j < INNER; j++)
			result[i + j] = arr[i + j] * arr2[i + j];
	}

	time_point<system_clock> epoch = system_clock::now();
	microseconds us = duration_cast<microseconds>(epoch - now);

	return us.count();
}


//  *** PERFORMANCE ANALYSIS ***
void print_table_title() {
	cout << "    ***** Version Name *****     | min(us)   | mean(us)  | stddev   | GOp/s     |  GB/s     |   CPI     | speedup   |";
	cout << endl;
}
void print_row(string name, _int64 time, _int64 time_mean, _int64 time_stddev, _int64 nbrOperations, _int64 nbrBytes, _int64 ticksPerMilliSecond, _int64 referenceTime) {
	const char separator = ' ';
	const int nameWidth = 32;
	const int numWidth = 9;

	if (name.length() > nameWidth)
		name = name.substr(0, nameWidth);
	cout << left << setw(nameWidth) << setfill(separator) << name << " | ";
	cout << right << setw(numWidth) << setfill(separator) << time << " | ";
	cout << right << setw(numWidth) << setfill(separator) << time_mean << " | ";
	cout << right << setw(numWidth-4) << setfill(separator) << (time_stddev * 100.0 / time_mean) << "% | ";
	cout << right << setw(numWidth) << setfill(separator) << (float)nbrOperations / time / 1000 << " | ";
	cout << right << setw(numWidth) << setfill(separator) << (float)nbrBytes / time / 1000 << " | ";
	float total_nbr_cycles = (float)(time * (ticksPerMilliSecond / 1000));
	cout << right << setw(numWidth) << setfill(separator) << ((float)total_nbr_cycles / nbrOperations) << " | ";
	cout << right << setw(numWidth) << setfill(separator) << (float)referenceTime / time << " | ";
	cout << endl;

}
void analyzePerformance(vector<string> names, _int64 runtimes[NBR_ALGORITHM_VERSIONS][NBR_EXPERIMENTS], _int64 totalNbrOfOperations, _int64 totalNbrOfBytes, _int64 ticksPerMilliSecond, _int64 referenceTime) {
	print_table_title();
	for (int v = 0; v < names.size(); v++) {
		_int64 time = minimalValue(runtimes[v], NBR_EXPERIMENTS);
		_int64 time_mean = meanValue(runtimes[v], NBR_EXPERIMENTS);
		_int64 time_stddev = stddev(runtimes[v], NBR_EXPERIMENTS);
		print_row(names[v], time, time_mean, time_stddev, totalNbrOfOperations, totalNbrOfBytes, ticksPerMilliSecond, referenceTime);
	}
}
// *** utility functions ***
// we compare the output of the 2 versions and expect no significant differences
void checkIfResultsAreTheSame(string name, int* arr3, int* arr4, int n) {
	int nbr_diff = 0;
	for (int i = 0; i < n; i++) {
		float rel_diff = arr3[i] == arr4[i] ? 0 : (arr3[i] - arr4[i]) / (arr3[i] == 0 ? arr4[i] : arr3[i]);
		if ( rel_diff > 0.0001) {
			nbr_diff++;
			if (PRINT_DATA  && i < 10) cout << arr3[i] << "<>" << arr4[i] << " ("<< rel_diff<<"), ";
		}
		else {
			if (PRINT_DATA  && i < 10) cout << arr3[i] << "==" << arr4[i] << " (" << rel_diff << "), ";
		}
		arr4[i] = 0; // we reset arr4 for further usage
	}
	if (PRINT_DATA) cout << endl;
	if (nbr_diff > 0)
		cout << "Problem with algorithm "<<name<<": " << nbr_diff << " differences with Original Algorithm." << endl;
}

_int64 minimalValue(_int64* values, int NBR) {
	_int64 min = values[0];
	for (int i = 1; i < NBR; i++) {
		if (values[i] < min)
			min = values[i];
	}
	return min;
}
_int64 meanValue(_int64* values, int NBR) {
	_int64 sum = values[0];
	for (int i = 1; i < NBR; i++) {
		sum += values[i];
	}
	return sum / NBR;
}
_int64 stddev(_int64* values, int NBR) {
	_int64 mean = meanValue(values, NBR);
	_int64 SSE = 0;
	for (int i = 0; i < NBR; i++) {
		SSE += (values[i] - mean) * (values[i] - mean);
	}
	return sqrt(SSE / NBR);
}
#pragma once

_int64 version_c_Od_NoIntrinsics(int n, int* arr, int* arr2, int* result);

_int64 version_c_Od_NoIntrinsics_nopragma(int n, int* arr, int* arr2, int* result);

_int64 version_Od_ManualLoopUnrolling(int n, int* arr, int* arr2, int* result);
_int64 version_Od_PragmaUnroll(int n, int* arr, int* arr2, int* result);
_int64 version_Od_PragmaUnrollInner(int n, int* arr, int* arr2, int* result);

_int64 version_Od_xFunction(int n, int* arr, int* arr2, int* result);

_int64 version_Od_xFunction_inline(int n, int* arr, int* arr2, int* result);

_int64 version_test8(int n, int* arr, int* arr2, int* result);

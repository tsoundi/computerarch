#pragma once

_int64 version_c_Od_NoIntrinsics(int n, short* arr, short* arr2, short* result);

_int64 version_c_Od_NoIntrinsics_nopragma(int n, short* arr, short* arr2, short* result);

_int64 version_Od_ManualLoopUnrolling(int n, short* arr, short* arr2, short* result);
_int64 version_Od_PragmaUnroll(int n, short* arr, short* arr2, short* result);
_int64 version_Od_PragmaUnrollInner(int n, short* arr, short* arr2, short* result);

_int64 version_Od_xFunction(int n, short* arr, short* arr2, short* result);

_int64 version_Od_xFunction_inline(int n, short* arr, short* arr2, short* result);

_int64 version_test8(int n, short* arr, short* arr2, short* result);

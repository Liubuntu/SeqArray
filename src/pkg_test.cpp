// ===========================================================
//
// pkg_test.cpp: package testing with C/C++ codes
//
// Copyright (C) 2016    Xiuwen Zheng
//
// This file is part of SeqArray.
//
// SeqArray is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License Version 3 as
// published by the Free Software Foundation.
//
// SeqArray is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SeqArray.
// If not, see <http://www.gnu.org/licenses/>.

#include "vectorization.h"
#include <R.h>
#include <Rdefines.h>

extern "C"
{

SEXP test_array_popcnt32(SEXP val)
{
	int n = length(val);
	int *s = INTEGER(val);
	SEXP rv_ans = NEW_INTEGER(n);
	int *p = INTEGER(rv_ans);
	for (int i=0; i < n; i++)
		p[i] = POPCNT_U32(s[i]);
	return rv_ans;
}

SEXP test_array_popcnt64(SEXP v1, SEXP v2)
{
	int n = length(v1);
	if (n != length(v2))
		error("error in 'test_popcnt64'.");
	int *s1 = INTEGER(v1), *s2 = INTEGER(v2);
	SEXP rv_ans = NEW_INTEGER(n);
	int *p = INTEGER(rv_ans);
	for (int i=0; i < n; i++)
	{
		uint64_t v = ((uint64_t)s1[i]) << 32 | (uint64_t)s2[i];
		p[i] = POPCNT_U64(v);
	}
	return rv_ans;
}

}
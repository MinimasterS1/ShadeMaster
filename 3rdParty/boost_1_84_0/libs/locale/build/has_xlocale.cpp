//
// Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <xlocale.h>
int main()
{
    newlocale(LC_ALL_MASK, "", 0);
}
#!/bin/sh
set -x
libtoolize -f -c
aclocal
autoheader
automake --copy --gnu --add-missing
autoconf

#!/bin/sh
autoreconf --install --force
./configure --with-boost=`pwd`/boost --enable-gcov
make
make check

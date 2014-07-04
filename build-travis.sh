#!/bin/sh
autoreconf --install --force
./configure --enable-gcov
make
make check

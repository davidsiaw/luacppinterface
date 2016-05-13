#!/bin/sh
ruby generate.rb
autoreconf --install --force
./configure --enable-gcov
make
make check

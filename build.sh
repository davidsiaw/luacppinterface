#!/bin/sh
autoreconf --install --force
./configure --with-boost=`pwd`/boost
make

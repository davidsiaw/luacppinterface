#!/bin/bash
autoreconf --install --force && ./configure --with-boost=`pwd`/boost && make && make check
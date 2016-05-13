#!/bin/sh
ruby generate.rb
autoreconf --install --force
./configure
make

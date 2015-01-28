#!/bin/bash
ls /usr/lib/libg*
ls /usr/include/gmock
ls /usr/src
cd /usr/src/gmock
cmake . 
make
mv libg* /usr/lib/
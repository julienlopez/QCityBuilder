#!/bin/bash
cd /usr/src/gmock
cmake . 
make
mv libg* /usr/lib/
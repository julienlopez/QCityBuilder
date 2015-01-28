#!/bin/bash

OBJ_DIR=$PWD/obj_lib
QMAKE=qmake

function error_exit
{
	echo "$1" 1>&2
	exit 1
}

$QMAKE "COVERAGE=1" && make VERBOSE=1

[ $? -ne 0 ] && error_exit "Compile step failed."

lcov --zerocounters --directory $OBJ_DIR -b $PWD/lib --no-external #> lcov.log 2> lcov.err
lcov --capture --initial --directory $OBJ_DIR -b $PWD/lib --no-external --output-file app #>> lcov.log 2>> lcov.err

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/bin/
bin/tests

echo "analyzing coverage data..."

lcov --no-checksum --directory $OBJ_DIR -b $PWD/lib --no-external --capture --output-file app.info #>> lcov.log 2>> lcov.err
genhtml -o cov-html app.info #>> lcov.log 2>> lcov.err

echo "done!"


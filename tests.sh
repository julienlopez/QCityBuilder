#!/bin/bash

OBJ_DIR=$PWD/obj_lib
QMAKE=qmake

DIR_OPTIONS="--base-directory $PWD/lib --directory $OBJ_DIR" #--directory obj_tests --directory tests

function error_exit
{
	echo "$1" 1>&2
	exit 1
}

$QMAKE "COVERAGE=1" && make VERBOSE=1

[ $? -ne 0 ] && error_exit "Compile step failed."

lcov --zerocounters $DIR_OPTIONS #> lcov.log 2> lcov.err
lcov --capture --initial $DIR_OPTIONS --output-file app.baseline #>> lcov.log 2>> lcov.err

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/bin/
bin/tests

echo "analyzing coverage data...: lcov --no-checksum $DIR_OPTIONS --capture --output-file app"
lcov --no-checksum $DIR_OPTIONS --capture --output-file app #>> lcov.log 2>> lcov.err
#lcov --no-checksum $DIR_OPTIONS --capture --output-file app.info

echo "merging datas"
lcov --add-tracefile app.baseline --add-tracefile app --output-file app.info

echo "removing useless data"
lcov --remove app.info "/usr*" --output-file app.info

echo "generation html doc"
genhtml -o cov-html app.info #>> lcov.log 2>> lcov.err

echo "done!"


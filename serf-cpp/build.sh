#!/bin/bash

function ShowUsage()
{
    cat <<EOT
$(basename "$0") options
    [--builddir=<builddir>]  - name of build directory
    [--cxx=<path/to/cxx>]    - path for CXX environment variable
    [--cc=<path/to/cc>]      - path for CC env variable
    [--cmake=<options>]      - option string to pass to CMake
    [--cover]                - generate unit test and code coverage reports
    [--concourse]            - building in Concourse
EOT
    return 0    
}

BUILDDIR=build
PARAM_CC=
PARAM_CXX=
PARAM_CMAKE=
PARAM_COVER=0
PARAM_CONCOURSE=

while test $# -gt 0; do
    param="$1"
    if test "${1::1}" = "-"; then
        if test ${#1} -gt 2 -a "${1::2}" = "--" ; then
            param="${1:2}"
        else
            param="${1:1}"
        fi
    else
        break
    fi

    shift

    case $param in
    builddir=*)
        BUILDDIR=$(echo "$param"|cut -f2 -d'=')
        ;;
    cc=*)
        PARAM_CC=$(echo "$param"|cut -f2 -d'=')
        ;;
    cxx=*)
        PARAM_CXX=$(echo "$param"|cut -f2 -d'=')
        ;;
    cmake=*)
        PARAM_CMAKE=$(echo "$param"|cut -f2- -d'=')
        ;;
    cover)
        PARAM_COVER=1
        ;;
    concourse*)
        PARAM_CONCOURSE=1
        ;;
    help|h|?|-?)
        ShowUsage
        exit 0
        ;;
    *)
        echo "Error: Unknown parameter: $param"
        ShowUsage
        exit 2
        ;;    
    esac
done

if [ $PARAM_COVER -eq 1 ]; then
    PARAM_CMAKE="$PARAM_CMAKE -DSERF_CPP_BUILD_COVERAGE=ON"
fi


echo "BUILDDIR=$BUILDDIR"
echo "PARAM_CC=$PARAM_CC"
echo "PARAM_CXX=$PARAM_CXX"
echo "PARAM_CMAKE=$PARAM_CMAKE"
echo "PARAM_COVER=$PARAM_COVER"

# If running in a Concourse pipeline then validate the repo was cloned
if [ -n "$PARAM_CONCOURSE" ]; then
    [ ! -d ./serf-cpp-git ] && { echo "ERROR: repo not cloned!"; exit 1; }

    # Change to the base directory of the repo
    cd serf-cpp-git || exit
fi

# Create build directory and switch to it
mkdir -p "$BUILDDIR"
cd "$BUILDDIR" || exit

# Configure via CMake
if [ -n "$PARAM_CXX" ] || [ -n "$PARAM_CC" ]; then
    # Override CC and CXX
    CC=$PARAM_CC CXX=$PARAM_CXX cmake "$PARAM_CMAKE" -DCMAKE_BUILD_TYPE=DEBUG -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=ON ..
else
    cmake "$PARAM_CMAKE" -DSERF_CPP_BUILD_EXAMPLE=ON -DSERF_CPP_BUILD_TESTS=ON ..
fi
ret=$?
[ $ret -ne 0 ] && exit $ret

# Build
make
ret=$?
[ $ret -ne 0 ] && exit $ret

if [ $PARAM_COVER -eq 1 ]; then
    # Run SerfCppCoverage to get unit test report and code coverage info
    make SerfCppCoverage
    ret=$?
    if [ $ret -eq 0 ]; then
        # Generate unit test html report and post to artstore
        junit2html unittests.xml index.html
        curl -F item=@index.html -F item=@index.html http://fir.love.io:3004/artstore/serf-cpp/unit
        echo "Unit Test Report: http://fir.love.io:3004/dev/serf-cpp/unit/"

        # Create code coverage tarball
        cd SerfCppCoverage/ || exit
        tar zcf ../coverage.tar.gz . 
        cd - || exit
        curl -F item=@coverage.tar.gz http://fir.love.io:3004/artstore/serf-cpp/coverage
        echo "Code Coverage: http://fir.love.io:3004/dev/serf-cpp/coverage/"
    fi
else

    [ ! -x ./tests/SerfCppTests ] && { echo "ERROR: unit tests not built!"; exit 1; }

    # Run unit tests
    ./tests/SerfCppTests
    ret=$?

fi

# Return result
exit $ret

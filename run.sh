#!/bin/bash

export CPRO_LOCAL=".local"
export CPRO_WORK=".work"

export CPRO_CMAKE_VERSION="3.27.9"
export CPRO_NINJA_VERSION="1.11.1"

export CPRO_CMAKE="${CPRO_LOCAL}/cmake/bin/cmake.exe"
export CPRO_CTEST="${CPRO_LOCAL}/cmake/bin/ctest.exe"
export CPRO_NINJA="${CPRO_LOCAL}/ninja/ninja.exe"
export CPRO_VCPKG="${CPRO_LOCAL}/vcpkg/vcpkg.exe"

if [ "$1" == "" -o "$1" == "help" -o "$1" == "-?" ]; then
	source shell/help.sh
	func_help
else
	source shell/functions.sh
	func_$1 ${@:2} || exit $?
fi

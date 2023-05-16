#!/bin/bash

export CPRO_LOCAL=".local"
export CPRO_WORK=".work"

export CPRO_CMAKE_VERSION="3.26.3"
export CPRO_NINJA_VERSION="1.11.1"

export CPRO_CMAKE="${CPRO_LOCAL}/cmake/bin/cmake.exe"
export CPRO_NINJA="${CPRO_LOCAL}/ninja/ninja.exe"
export CPRO_VCPKG="${CPRO_LOCAL}/vcpkg/vcpkg.exe"

if [ "$1" == "setup" ]; then

	mkdir -p ${CPRO_LOCAL}
	cd ${CPRO_LOCAL}

	curl -L -O https://github.com/Kitware/CMake/releases/download/v${CPRO_CMAKE_VERSION}/cmake-${CPRO_CMAKE_VERSION}-windows-x86_64.zip || exit $?
	unzip -q cmake-${CPRO_CMAKE_VERSION}-windows-x86_64.zip || exit $?
	mv cmake-${CPRO_CMAKE_VERSION}-windows-x86_64 cmake || exit $?

	curl -L -O https://github.com/ninja-build/ninja/releases/download/v${CPRO_NINJA_VERSION}/ninja-win.zip || exit $?
	unzip -q ninja-win.zip -d ninja || exit $?

	git clone --depth=1 https://github.com/Microsoft/vcpkg.git || exit $?
	cd vcpkg
	./bootstrap-vcpkg.bat -disableMetrics || exit $?

	cd ../..

elif [ "$1" == "project" ]; then

	if [ "$2" == "open" ]; then
		if [ -f "${CPRO_WORK}/vs/project/CPro.sln" ]; then
			start "${CPRO_WORK}/vs/project/CPro.sln"
		else
			"C:\Program Files\Microsoft Visual Studio\2022\Professional\Common7\IDE\devenv.exe" . &
		fi
		exit 0
	fi

	${CPRO_CMAKE} --preset $2 || exit $?

elif [ "$1" == "build" ]; then

	${CPRO_CMAKE} --build --preset $2 || exit $?

elif [ "$1" == "run" ]; then

	"${CPRO_WORK}/vs/project/src/app/Debug/app.exe" || exit $?

elif [ "$1" == "reset-local" ]; then

	rm -rf ${CPRO_LOCAL} || exit $?

elif [ "$1" == "reset-work" ]; then

	rm -rf ${CPRO_WORK} || exit $?

fi
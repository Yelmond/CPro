function func_setup {
	mkdir -p ${CPRO_LOCAL}
	cd ${CPRO_LOCAL}

	local CMAKE_DOWNLOAD_URL="https://github.com/Kitware/CMake/releases/download/v${CPRO_CMAKE_VERSION}"
	local NINJA_DOWNLOAD_URL="https://github.com/ninja-build/ninja/releases/download/v${CPRO_NINJA_VERSION}"

	local OS="$(uname)"
	if [ "$OS" == "Linux" ]; then
		source "../shell/functions_linux.sh"
		func_setup_linux || return $?
	elif [ "$OS" == "Darwin" ]; then
		source "../shell/functions_mac.sh"
		func_setup_mac || return $?
	elif [[ "$OS" == "MINGW"* || "$OS" == "MSYS"* ]]; then
		source "../shell/functions_win.sh"
		func_setup_win || return $?
	else
		echo "Unsupported: Unknown operating system: $(uname)"
		return 1
	fi

	git clone --depth=1 https://github.com/Microsoft/vcpkg.git || return $?
	cd vcpkg
	export VCPKG_DEFAULT_BINARY_CACHE="${CPRO_LOCAL}/vcpkg_archives"
	if [[ "$OS" == "MINGW"* || "$OS" == "MSYS"* ]]; then
		./bootstrap-vcpkg.bat -disableMetrics || return $?
	else
		./bootstrap-vcpkg.sh -disableMetrics || return $?
	fi

	cd ../..
}

function func_open {
	if [ "$1" == "sln" ]; then
		if [ -f "${CPRO_WORK}/vs/project/CPro.sln" ]; then
			start "${CPRO_WORK}/vs/project/CPro.sln"
		else
			echo "CPro.sln not found."
		fi
	elif [ "$1" == "vs" ]; then
		if [ -f "C:\Program Files\Microsoft Visual Studio\2022\Professional\Common7\IDE\devenv.exe" ]; then
			"C:\Program Files\Microsoft Visual Studio\2022\Professional\Common7\IDE\devenv.exe" . &
		elif [ -f "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.exe" ]; then
			"C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.exe" . &
		else
			echo "Visual Studio not found."
		fi
	fi
}

function func_project {
	if [ -z "$1" ]; then
		${CPRO_CMAKE} --list-presets || return $?
		return 1
	fi

	${CPRO_CMAKE} --preset $1 || return $?
}

function func_build {
	if [ -z "$1" ]; then
		${CPRO_CMAKE} --list-presets || return $?
		return 1
	fi

	echo "Build:" || return $?
	${CPRO_CMAKE} --build --preset $1 || return $?
	echo "" || return $? # Just to add some space after the build output.
}

function func_run {
	if [ -z "$1" ]; then
		${CPRO_CMAKE} --list-presets || return $?
		return 1
	fi

	if [ ! -d "${CPRO_WORK}/$1" ]; then
		echo "Available options:"
		ls ${CPRO_WORK}
		return 1
	fi

	echo "Run:" || return $?
	"${CPRO_WORK}/$1/project/src/app/Debug/app.exe" || return $?
}

function func_test {
	if [ -z "$1" ]; then
		${CPRO_CMAKE} --list-presets || return $?
		return 1
	fi

	if [ ! -d "${CPRO_WORK}/$1" ]; then
		echo "Available options:"
		ls ${CPRO_WORK}
		return 1
	fi

	echo "Test:" || return $?
	${CPRO_CTEST} --preset $1 || return $?
}

function func_br {
	if [ ! -d "${CPRO_WORK}/$1" ]; then
		func_project $1 || return $?
	fi

	func_build $1 || return $?
	func_run $1 || return $?
}

function func_bt {
	if [ ! -d "${CPRO_WORK}/$1" ]; then
		func_project $1 || return $?
	fi

	func_build $1 || return $?
	func_test $1 || return $?
}

function func_resetlocal {
	rm -rf ${CPRO_LOCAL} || return $?
}

function func_resetwork {
	rm -rf ${CPRO_WORK} || return $?
}

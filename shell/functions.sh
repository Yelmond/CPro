function func_setup {
	mkdir -p ${CPRO_LOCAL}
	cd ${CPRO_LOCAL}

	curl -L -O https://github.com/Kitware/CMake/releases/download/v${CPRO_CMAKE_VERSION}/cmake-${CPRO_CMAKE_VERSION}-windows-x86_64.zip || return $?
	unzip -q cmake-${CPRO_CMAKE_VERSION}-windows-x86_64.zip || return $?
	mv cmake-${CPRO_CMAKE_VERSION}-windows-x86_64 cmake || return $?

	curl -L -O https://github.com/ninja-build/ninja/releases/download/v${CPRO_NINJA_VERSION}/ninja-win.zip || return $?
	unzip -q ninja-win.zip -d ninja || return $?

	git clone --depth=1 https://github.com/Microsoft/vcpkg.git || return $?
	cd vcpkg
	./bootstrap-vcpkg.bat -disableMetrics || return $?

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
	${CPRO_CMAKE} --preset $1 || return $?
}

function func_build {
	${CPRO_CMAKE} --build --preset $1 || return $?
}

function func_run {
	"${CPRO_WORK}/$1/project/src/app/Debug/app.exe" || return $?
}

function func_br {
	func_build $1 || return $?
	func_run $1 || return $?
}

function func_resetlocal {
	rm -rf ${CPRO_LOCAL} || return $?
}

function func_resetwork {
	rm -rf ${CPRO_WORK} || return $?
}

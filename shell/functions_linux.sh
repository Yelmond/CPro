function func_setup_linux {
	local ARCH="$(uname -m)"
	if [ "$ARCH" == "x86_64" ]; then
		local CMAKE_ARCH="x86_64"
	elif [ "$ARCH" == "aarch64" ]; then
		local CMAKE_ARCH="aarch64"
	else
		echo "Unsupported: Unknown architecture: $ARCH"
		return 1
	fi

	local CMAKE_FILE_NAME="cmake-${CPRO_CMAKE_VERSION}-linux-${CMAKE_ARCH}"
	local CMAKE_ARCHIVE_NAME="${CMAKE_FILE_NAME}.tar.gz"

	curl -L -O ${CMAKE_DOWNLOAD_URL}/${CMAKE_ARCHIVE_NAME} || return $?
	tar -xzf ${CMAKE_ARCHIVE_NAME} || return $?
	mv ${CMAKE_FILE_NAME} cmake || return $?

	curl -L -O ${NINJA_DOWNLOAD_URL}/ninja-linux.zip || return $?
	unzip -q ninja-linux.zip -d ninja || return $?
}

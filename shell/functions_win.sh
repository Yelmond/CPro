function func_setup_win {
	if [ "$PROCESSOR_ARCHITECTURE" == "AMD64" ]; then
		local CMAKE_ARCH="x86_64"
	elif [ "$PROCESSOR_ARCHITECTURE" == "ARM64" ]; then
		local CMAKE_ARCH="arm64"
	else
		echo "Unsupported: Unknown architecture: $PROCESSOR_ARCHITECTURE"
		return 1
	fi

	local CMAKE_FILE_NAME="cmake-${CPRO_CMAKE_VERSION}-windows-${CMAKE_ARCH}"
	local CMAKE_ARCHIVE_NAME="${CMAKE_FILE_NAME}.zip"

	curl -L -O ${CMAKE_DOWNLOAD_URL}/${CMAKE_ARCHIVE_NAME} || return $?
	unzip -q ${CMAKE_ARCHIVE_NAME} || return $?
	mv ${CMAKE_FILE_NAME} cmake || return $?

	curl -L -O ${NINJA_DOWNLOAD_URL}/ninja-win.zip || return $?
	unzip -q ninja-win.zip -d ninja || return $?
}

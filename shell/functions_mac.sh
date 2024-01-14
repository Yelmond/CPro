function func_setup_mac {
	local CMAKE_FILE_NAME="cmake-${CPRO_CMAKE_VERSION}-macos-universal"
	local CMAKE_ARCHIVE_NAME="${CMAKE_FILE_NAME}.tar.gz"

	curl -L -O ${CMAKE_DOWNLOAD_URL}/${CMAKE_ARCHIVE_NAME} || return $?
	tar -xzf ${CMAKE_ARCHIVE_NAME} || return $?
	mv ${CMAKE_FILE_NAME} cmake || return $?

	curl -L -O ${NINJA_DOWNLOAD_URL}/ninja-mac.zip || return $?
	unzip -q ninja-mac.zip -d ninja || return $?
}

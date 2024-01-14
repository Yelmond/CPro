function func_help() {
	echo "Available commands:"
	echo ""
	echo "  setup             Set up the environment."
	echo "  open [sln|vs]     Open the project in Visual Studio."
	echo "                    'sln' opens the .sln file,"
	echo "                    'vs' opens Visual Studio."
	echo "  project [preset]  Use a preset for the project."
	echo "  build [preset]    Build the project using a preset."
	echo "  run [preset]      Run the specified preset."
	echo "  br [preset]       Build and run the specified preset."
	echo "  resetlocal        Delete all files in the local directory."
	echo "  resetwork         Delete all files in the work directory."
	echo ""

	if [ ! -f "${CPRO_CMAKE}" ]; then
		echo "Available presets:"
		echo "  CMake not found. Run 'setup' to set up the environment."
		return 0
	fi

	${CPRO_CMAKE} --list-presets=all || return $?
}

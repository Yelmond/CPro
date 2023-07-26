function func_help() {
	echo "Available commands:"
	echo "  setup             Set up the environment."
	echo "  open [sln|vs]     Open the project in Visual Studio. 'sln' opens the .sln file, 'vs' opens Visual Studio."
	echo "  project [preset]  Use a preset for the project."
	echo "  build [preset]    Build the project using a preset."
	echo "  run [project]     Run the specified project."
	echo "  resetlocal        Delete all files in the local directory."
	echo "  resetwork         Delete all files in the work directory."
}

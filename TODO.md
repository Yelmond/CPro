Code Samples:
- https://github.com/AnthonyCalandra/modern-cpp-features

Reading:
- https://betterprogramming.pub/tricks-for-successfully-using-vcpkg-in-c-and-c-projects-b775cc836d81
- https://learn.microsoft.com/en-us/cpp/build/walkthrough-header-units?view=msvc-170
- https://www.kitware.com/import-cmake-c20-modules/
- Google Test: https://www.youtube.com/watch?v=Lp1ifh9TuFI

Add GitHub Actions:
- add caching: https://docs.github.com/en/actions/using-workflows/caching-dependencies-to-speed-up-workflows
- fix linux build:
	- https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#manual:cmake-compile-features(7)
	- https://gitlab.kitware.com/cmake/cmake/-/issues/18275

CMake:
- ui should be a SHARED library, but that doesn't compile atm

Next Lessons:
- std::views::iota
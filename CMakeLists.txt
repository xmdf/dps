cmake_minimum_required(VERSION 3.17)

project(PROJECT_NAME VERSION 0.0.1)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories
add_subdirectory(src)

# Add tests
enable_testing()
add_subdirectory(tests)

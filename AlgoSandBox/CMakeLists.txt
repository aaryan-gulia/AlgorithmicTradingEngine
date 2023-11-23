cmake_minimum_required(VERSION 3.2.0)
project(Sandbox)

# Find the AlgorithmicTradingEngine library
find_package(AlgorithmicTradingEngine REQUIRED)

# Add the main.cpp source file
add_executable(sandbox main.cpp)

# Link the AlgorithmicTradingEngine library to the sandbox executable
target_link_libraries(sandbox AlgorithmicTradingEngine)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Add the necessary include directories
include_directories(${AlgorithmicTradingEngine_INCLUDE_DIR})
cmake_minimum_required(VERSION 3.9)
project(AlgorithmicTradingEngine)


set(CMAKE_CXX_STANDARD 17)
# Define source directories

set(SOURCE_DIRS)
file(GLOB_RECURSE SOURCE_DIRS **.cpp)

file(GLOB_RECURSE REMOVE_CMAKE "cmake-build-debug/*")
list(REMOVE_ITEM SOURCE_DIRS ${REMOVE_CMAKE})

# Find external dependencies
find_package(JSONCPP REQUIRED)
find_package(CURL REQUIRED)

#add executable
add_executable(AlgorithmicTradingEngine ${SOURCE_DIRS})

# Link external dependencies
include_directories(${JSONCPP_INCLUDE_DIR} ${CURL_INCLUDE_DIR})

target_link_libraries(AlgorithmicTradingEngine jsoncpp_lib ${CURL_LIBRARIES})
cmake_minimum_required(VERSION 3.16)
project(AlgorithmicTradingEngine)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
# Define source directories
set(SOURCE_DIRS)
file(GLOB_RECURSE SOURCE_DIRS MarketDataProviders/*.cpp)

# Find external dependencies
find_package(JSONCPP REQUIRED)
find_package(CURL REQUIRED)
# Add source files and set output directory
add_library(AlgorithmicTradingEngine SHARED ${SOURCE_DIRS})
target_sources(AlgorithmicTradingEngine PUBLIC ${SOURCE_DIRS})
set_target_properties(AlgorithmicTradingEngine PROPERTIES EXCLUDE_FROM_DEFAULT_CONFIG ON)

# Link external dependencies
include_directories(${JSONCPP_INCLUDE_DIR} ${CURL_INCLUDE_DIR})

target_link_libraries(AlgorithmicTradingEngine jsoncpp_lib ${CURL_LIBRARIES})

# Set MacOS specific build settings
if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()
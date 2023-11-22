cmake_minimum_required(VERSION 3.2.0)
project(AlgorithmicTradingEngine)

# Find the JSONCPP, Boost, and libcurl libraries
find_package(JSONCPP REQUIRED)
find_package(Boost REQUIRED)
find_package(CURL REQUIRED)
link_libraries(${JSONCPP_LIBRARIES})
include_directories(${CURL_INCLUDE_DIR})

set(MARKET_DATA_PROVIDER_SOURCES
        MarketDataProviders/MarketDataProvider.cpp
        MarketDataProviders/AlphaVantageProvider.cpp
        MarketDataProviders/MarketDataProviderFactory.cpp
        MarketDataProviders/MarketDataAccess.cpp
)

add_executable(main main ${MARKET_DATA_PROVIDER_SOURCES})

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Add the source files to the project
set(SOURCE_FILES
        MarketDataProviders/MarketDataProvider.cpp
        MarketDataProviders/AlphaVantageProvider.cpp
        MarketDataProviders/MarketDataProviderFactory.cpp
        MarketDataProviders/MarketDataAccess.cpp
)

target_sources(main PRIVATE ${SOURCE_FILES})

# Add the necessary include directories
include_directories(${JSONCPP_INCLUDE_DIR} ${Boost_INCLUDE_DIR} ${CURL_INCLUDE_DIR})

# Link the MarketDataProviders directory with PUBLIC visibility
target_link_directories(main PUBLIC MarketDataProviders)

target_link_libraries(main jsoncpp_lib Boost::boost ${CURL_LIBRARIES})

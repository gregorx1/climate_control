cmake_minimum_required(VERSION 3.10)

project(ClimateControlTest)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_subdirectory(googletest)

# Add the source files for the unit test
set(SOURCE_FILES src/TemperatureControlImpl.cpp test/TemperatureControlTest.cpp)

add_executable(ClimateControlTest ${SOURCE_FILES})

target_link_libraries(ClimateControlTest gtest gmock pthread)

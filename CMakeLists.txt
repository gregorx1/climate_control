cmake_minimum_required(VERSION 3.10)

project(ClimateControlTest)

set(CMAKE_CXX_STANDARD 11)

#find_package(GMock REQUIRED)
find_package(GTest REQUIRED)

include_directories(include)
include_directories(${GTEST_INCLUDE_DIRS})
#include_directories(${GMOCK_INCLUDE_DIRS})

# Add the source files for the unit test
set(SOURCE_FILES src/TemperatureControlImpl.cpp test/TemperatureControlTest.cpp)

# Create the executable for the unit test
add_executable(ClimateControlTest ${SOURCE_FILES})

# Link the unit test executable with the Google Test and Google Mock libraries
#target_link_libraries(ClimateControlTest gtest gmock pthread)

target_link_libraries(ClimateControlTest  ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES} pthread)


#target_compile_definitions(ClimateControlTest ${GTEST_DEFINITIONS} ${GMOCK_DEFINITIONS})
target_compile_definitions(ClimateControlTest PRIVATE ${GTEST_DEFINITIONS})

cmake_minimum_required(VERSION 3.17)
project(Entrega2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# Google tests
set(GOOGLE_TEST_DIRECTORY lib/googletest-master)
add_subdirectory(${GOOGLE_TEST_DIRECTORY})
include_directories(${GOOGLE_TEST_DIRECTORY}/googlemock/include)
include_directories(${GOOGLE_TEST_DIRECTORY}/googletest/include)

# Build GraphViewer
set(GRAPHVIEWERCPP_PATH lib/GraphViewerCpp)
add_subdirectory(${GRAPHVIEWERCPP_PATH})
include_directories(${GRAPHVIEWERCPP_PATH}/include)

add_executable(Entrega2 main.cpp Algorithms/Graph.h Algorithms/MutablePriorityQueue.h FileHandling.h Utils.h Tests/TarjanTest.cpp)

target_link_libraries(Entrega2 gtest gtest_main)
target_link_libraries(Entrega2 graphviewer)
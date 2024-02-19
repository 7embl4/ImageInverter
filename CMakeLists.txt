cmake_minimum_required (VERSION 3.8)
project ("ImageInverter")

set(CMAKE_CXX_STANDARD 17)

# include opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# add executable and link libs
add_executable (${PROJECT_NAME} "src/main.cpp" )
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
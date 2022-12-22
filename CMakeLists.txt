cmake_minimum_required(VERSION "3.17")

# name of this example project
project(simple-demo)


set(OpenCV_DIR /Users/siddharthdas/cv_works/opencv/install/lib/cmake/opencv4)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )

# tell the build to include the headers from OpenCV
include_directories( ${OpenCV_INCLUDE_DIRS} )

# specify the executable target to be built
# src/interactiveColorSegment.cc
add_executable(simpledemo src/utils.cc)

# tell it to link the executable target against OpenCV
target_link_libraries(simpledemo ${OpenCV_LIBS} )
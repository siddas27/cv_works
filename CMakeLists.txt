cmake_minimum_required(VERSION 3.22)
project(VisionC)

set(CMAKE_CXX_STANDARD 17)

# Fetch from git
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#FetchContent_Declare(
#            opencv
 #           GIT_REPOSITORY https://github.com/opencv/opencv.git
 #           GIT_TAG        4.4.0
#)
#FetchContent_MakeAvailable(opencv)

set(OpenCV_DIR /tmp/build/vscode/)
find_package( OpenCV REQUIRED)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

cmake_minimum_required(VERSION 3.22)
project(utils C CXX)

set(SOURCE_FILES
    utils.h
    utils.cc
)

add_library(utils SHARED STATIC ${SOURCE_FILES})


target_link_libraries(utils PUBLIC
    ${OpenCV_LIBS}
)

# install(TARGETS utils DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
# install(FILES utils.h DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})
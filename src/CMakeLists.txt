cmake_minimum_required(VERSION 3.8)

set(This Src_Pro)

set(Headers
)

set(Sources
    main.cc
)

add_subdirectory(utils)

add_executable(${This} ${Sources} ${Headers})

target_link_libraries(${This} PUBLIC
    ${OpenCV_LIBS}
    utils
)

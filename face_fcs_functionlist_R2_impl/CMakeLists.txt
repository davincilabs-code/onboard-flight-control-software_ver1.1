cmake_minimum_required(VERSION 3.16)
project(face_fcs_functionlist_R2_impl C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/common)

file(GLOB_RECURSE SRC_COMMON ${PROJECT_SOURCE_DIR}/common/*.c)
file(GLOB_RECURSE SRC_PCS    ${PROJECT_SOURCE_DIR}/pcs/*.c)
file(GLOB_RECURSE SRC_PSSS   ${PROJECT_SOURCE_DIR}/psss/*.c)
file(GLOB_RECURSE SRC_OSS    ${PROJECT_SOURCE_DIR}/oss/*.c)
file(GLOB_RECURSE SRC_IOSS   ${PROJECT_SOURCE_DIR}/ioss/*.c)

add_executable(demo
    ${PROJECT_SOURCE_DIR}/examples/demo_main.c
    ${SRC_COMMON}
    ${SRC_PCS}
    ${SRC_PSSS}
    ${SRC_OSS}
    ${SRC_IOSS}
)

if (UNIX)
    target_link_libraries(demo m)
endif()

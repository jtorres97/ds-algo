cmake_minimum_required(VERSION 3.1)
project(BTree)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Add more as needed
include_directories(${PROJECT_SOURCE_DIR}/includes)

# C++ 17 standard
set(CMAKE_CXX_STANDARD 17)

# Include all .cpp and .h in src and include directories respectively
file(GLOB
        SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp
        INCLUDE_FILES ${PROJECT_SOURCE_DIR}/*.h
        )

add_executable(BTree
        ${SRC_FILES}
        ${INCLUDE_FILES}
        )
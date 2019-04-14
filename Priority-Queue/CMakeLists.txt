cmake_minimum_required(VERSION 3.1)
project(Priority-Queue)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Add more as needed
include_directories(${PROJECT_SOURCE_DIR}/include)

# C++ 17 standard
set(CMAKE_CXX_STANDARD 17)

# Include all .cpp and .h in src and include directories respectively
file(GLOB
        SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp
        INCLUDE_FILES ${PROJECT_SOURCE_DIR}/include/*.h
        )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/names.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Priority-Queue
        ${SRC_FILES}
        ${INCLUDE_FILES}
        )
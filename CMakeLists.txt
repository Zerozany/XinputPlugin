cmake_minimum_required(VERSION 3.20)

project(XinputPlugin VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_LIST ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${SRC_LIST})

# add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
file(GLOB LIBS_LIST ${PROJECT_SOURCE_DIR}/libs/*.lib)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBS_LIST})

project(KMeans)
cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11)


aux_source_directory(app MAIN)
aux_source_directory(src SRC_LIST)
INCLUDE_DIRECTORIES(include)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${MAIN})


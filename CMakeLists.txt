cmake_minimum_required(VERSION 3.1)
project(GeometricScene)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE main.cpp visitor.cpp figure.cpp Scene.cpp)
set(HEADER visitor.h Scene.h figure.h SceneElement.h)

add_executable(GeomScene ${SOURCE} ${HEADER})

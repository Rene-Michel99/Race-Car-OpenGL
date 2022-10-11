cmake_minimum_required(VERSION 3.23)
project(test)
set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED) # Works in CLion and terminal
find_package(GLUT REQUIRED) # Works only in terminal
include_directories(GL)

add_executable(test main.cpp Classes/car.cpp Classes/car.h Classes/road.cpp Classes/road.h Classes/light_pole.cpp Classes/light_pole.h)
target_link_libraries(test -lglut -lGLU -lGL)

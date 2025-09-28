cmake_minimum_required(VERSION 3.16)
project(GestionEducativa LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(gestion_educativa
    src/main.cpp
    src/Student.cpp
    src/Instructor.cpp
    src/Department.cpp
)

target_include_directories(gestion_educativa PRIVATE include data_structures)

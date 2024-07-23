cmake_minimum_required(VERSION 3.1)
project(simulation)

set(CMAKE_CXX_STANDARD 11)

find_package(pybind11 REQUIRED)

# Manually specify the Python paths
set(PYTHON_EXECUTABLE "/home/thinker0/.pyenv/versions/SANDBOX_312/bin/python3")
set(PYTHON_INCLUDE_DIR "/home/thinker0/.pyenv/versions/3.12.0b4/include/python3.12")
set(PYTHON_LIBRARY "/home/thinker0/.pyenv/versions/3.12.0b4/lib/libpython3.12.so")

include_directories(${PYTHON_INCLUDE_DIR})
link_directories(${PYTHON_LIBRARY})

add_library(simulation MODULE bindings.cpp)
target_link_libraries(simulation PRIVATE pybind11::module ${PYTHON_LIBRARY})

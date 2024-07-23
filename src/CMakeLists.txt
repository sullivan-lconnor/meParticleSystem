cmake_minimum_required(VERSION 3.1)
project(simulation)

set(CMAKE_CXX_STANDARD 11)

find_package(pybind11 REQUIRED)

# Manually specify the Python paths
set(PYTHON_EXECUTABLE /home/thinker0/.pyenv/versions/SANDBOX_310/bin/python)
set(PYTHON_INCLUDE_DIR /home/thinker0/.pyenv/versions/3.10.11/include/python3.10)
set(PYTHON_LIBRARY /home/thinker0/.pyenv/versions/3.10.11/lib/libpython3.10.so)

include_directories(${PYTHON_INCLUDE_DIR})
link_directories(${PYTHON_LIBRARY})

add_library(simulation MODULE bindings.cpp)
set_target_properties(simulation PROPERTIES PREFIX "" SUFFIX ".so")
target_link_libraries(simulation PRIVATE pybind11::module ${PYTHON_LIBRARY})

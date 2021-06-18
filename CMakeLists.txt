cmake_minimum_required(VERSION 3.20.2)

project(mailio VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(mailio mailio_sol.cpp)
target_link_libraries(mailio mailio.lib)

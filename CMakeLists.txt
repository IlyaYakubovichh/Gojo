cmake_minimum_required(VERSION 4.2.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

project(Gojo)

include(GNUInstallDirs)

add_subdirectory(GojoEngine)
add_subdirectory(Projects)
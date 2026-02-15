cmake_minimum_required(VERSION 4.2.1)
set(LocalRoot ${CMAKE_CURRENT_SOURCE_DIR})
project(GojoEngine)

# Files
file(GLOB_RECURSE Headers RELATIVE ${LocalRoot} *.h)
file(GLOB_RECURSE Cpps RELATIVE ${LocalRoot} *.cpp)
source_group(TREE ${LocalRoot} FILES ${Headers} ${Cpps})

# Setup target
add_library(GojoEngine SHARED ${Headers} ${Cpps})

target_precompile_headers(GojoEngine PRIVATE ${LocalRoot}/GojoEnginePch.h)
target_compile_definitions(GojoEngine PRIVATE GOJOENGINE_EXPORTS)
target_include_directories(GojoEngine PUBLIC ${LocalRoot}
											 ${LocalRoot}/Source
)

# Configure dependencies
include(GojoDependencies.cmake)
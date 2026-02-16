cmake_minimum_required(VERSION 4.2.1)
set(LocalRoot ${CMAKE_CURRENT_SOURCE_DIR})

# GojoEngine
project(GojoEngine)

# Files
file(GLOB_RECURSE Headers RELATIVE ${LocalRoot} *.h)
file(GLOB_RECURSE Cpps RELATIVE ${LocalRoot} *.cpp)
source_group(TREE ${LocalRoot} FILES ${Headers} ${Cpps})

# Setup target
add_library(GojoEngine SHARED ${Headers} ${Cpps})

# Definitions
target_compile_definitions(GojoEngine PRIVATE
    $<$<CONFIG:Debug>:GOJO_ASSERTIONS_ENABLED>
    $<$<CONFIG:Debug>:GOJO_DEBUG_BUILD>
    $<$<CONFIG:Release>:GOJO_ASSERTIONS_ENABLED>
    $<$<CONFIG:Release>:GOJO_RELEASE_BUILD>
)
target_precompile_headers(GojoEngine PRIVATE ${LocalRoot}/GojoEnginePch.h)
target_compile_definitions(GojoEngine PRIVATE GOJOENGINE_EXPORTS) # exposed into __desclspec(dllexport) or __declspec(dllimport)
target_include_directories(GojoEngine PUBLIC ${LocalRoot}
											 ${LocalRoot}/Source
)

GojoSensei(GojoEngine GojoEngine)

# Configure dependencies
include(GojoEngineDependencies.cmake)
cmake_minimum_required(VERSION 4.2.1)
set(LocalRoot ${CMAKE_CURRENT_SOURCE_DIR})

# GraphicsEditor
project(GraphicsEditor)

# Files
file(GLOB_RECURSE Headers RELATIVE ${LocalRoot} *.h)
file(GLOB_RECURSE Cpps RELATIVE ${LocalRoot} *.cpp)
source_group(TREE ${LocalRoot} FILES ${Headers} ${Cpps})

# Setup target
add_executable(GraphicsEditor ${Headers} ${Cpps})

target_link_libraries(GraphicsEditor PRIVATE GojoEngine)
target_include_directories(GraphicsEditor PRIVATE ${LocalRoot}
												  ${LocalRoot}/Source
)

# Copy GojoEngine dll to GraphicsEditor.exe dir
add_custom_command(TARGET GraphicsEditor 
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:GraphicsEditor> $<TARGET_RUNTIME_DLLS:GraphicsEditor>
	COMMAND_EXPAND_LISTS
)
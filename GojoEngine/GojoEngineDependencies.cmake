cmake_minimum_required(VERSION 4.2.1)
include(FetchContent)

# enable verbose output for FetchContent
set(FETCHCONTENT_QUIET OFF)


# ------------------------------------
# spdlog library
# ------------------------------------
FetchContent_Declare(
  spdlog
  URL https://github.com/gabime/spdlog/archive/refs/tags/v1.16.0.tar.gz
)
FetchContent_MakeAvailable(spdlog)
target_link_libraries(GojoEngine PUBLIC
	spdlog
)


# ------------------------------------
# GLFW library
# ------------------------------------
FetchContent_Declare(
  glfw
  URL https://github.com/glfw/glfw/archive/refs/tags/3.4.tar.gz
)
FetchContent_MakeAvailable(glfw)
target_link_libraries(GojoEngine PUBLIC
	glfw
)


# ------------------------------------
# Vulkan library
# ------------------------------------
find_package(Vulkan REQUIRED COMPONENTS shaderc_combined)
message(STATUS "Vulkan found: ${Vulkan_FOUND}")
message(STATUS "Vulkan include dirs: ${Vulkan_INCLUDE_DIRS}")
message(STATUS "Vulkan library: ${Vulkan_LIBRARY}")
message(STATUS "Vulkan volk library: ${Vulkan_volk_LIBRARY}")
message(STATUS "Vulkan shaderc_combined library: ${Vulkan_shaderc_combined_LIBRARY}")
target_link_options(GojoEngine INTERFACE LINKER:/IGNORE:4099)
target_link_libraries(GojoEngine PUBLIC 
	Vulkan::Vulkan
	Vulkan::shaderc_combined
)


# ------------------------------------
# vk-bootstrap library via FetchContent
# ------------------------------------
FetchContent_Declare(
  vkbootstrap
  URL https://github.com/charles-lunarg/vk-bootstrap/archive/refs/tags/v1.4.330.tar.gz
)
FetchContent_MakeAvailable(vkbootstrap)
target_link_libraries(GojoEngine PUBLIC 
	vk-bootstrap::vk-bootstrap
)


# ------------------------------------
# Finish
# ------------------------------------
GojoSensei(spdlog GojoEngine/GojoEngineDependencies)
GojoSensei(glfw GojoEngine/GojoEngineDependencies)
GojoSensei(vk-bootstrap GojoEngine/GojoEngineDependencies)
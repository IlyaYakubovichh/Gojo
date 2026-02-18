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
# Finish
# ------------------------------------
GojoSensei(spdlog GojoEngine/GojoEngineDependencies)
GojoSensei(glfw GojoEngine/GojoEngineDependencies)
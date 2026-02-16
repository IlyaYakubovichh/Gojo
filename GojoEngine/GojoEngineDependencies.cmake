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
# Finish
# ------------------------------------
GojoSensei(spdlog GojoEngine/GojoEngineDependencies)
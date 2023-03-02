# CMakeList.txt : CMake project for Singularity, include source and define
# project specific logic here.
#

# Add source to this project's executable.

file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.h")
add_executable(Singularity ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Singularity PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_link_libraries(Singularity PUBLIC Vulkan::Vulkan)

target_include_directories(Singularity PRIVATE "../vendor/glfw/include")
target_include_directories(Singularity PRIVATE "../vendor/spdlog/include")
target_include_directories(Singularity PUBLIC "../vendor/fmt/include")
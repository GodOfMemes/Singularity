# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Singularity")
find_package(Vulkan REQUIRED)

cmake_policy(SET CMP0079 NEW)

# Include sub-projects.
add_subdirectory ("Singularity")
add_subdirectory("vendor/glfw")
target_link_libraries(Singularity PRIVATE glfw)
add_subdirectory("vendor/spdlog")
target_link_libraries(Singularity PRIVATE spdlog::spdlog_header_only)
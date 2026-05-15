cmake_minimum_required(VERSION 3.10)

project(MotorCautare)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add ImGui source files directly
add_library(imgui
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC vendor/imgui vendor/imgui/backends)

# Find OpenGL and GLFW
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

# Main executable (now with GUI)
add_executable(motor_cautare_gui src/main_gui.cpp src/Document.cpp src/Index.cpp src/Logger.cpp)

# Link libraries to the GUI executable
target_link_libraries(motor_cautare_gui PRIVATE imgui OpenGL::GL ${GLFW_LIBRARIES})
target_include_directories(motor_cautare_gui PRIVATE ${GLFW_INCLUDE_DIRS})


# Original CLI executable (renamed)
add_executable(motor_cautare_cli src/main.cpp src/Document.cpp src/Index.cpp src/Logger.cpp)

# Tests executable
add_executable(test_index tests/test_index.cpp src/Document.cpp src/Index.cpp src/Logger.cpp)

# Enable testing
enable_testing()
add_test(NAME IndexTests COMMAND test_index)

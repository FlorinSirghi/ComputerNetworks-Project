cmake_minimum_required(VERSION 3.22)
project(Client)

set(CMAKE_CXX_STANDARD 14)

add_library(
        imgui
        Vendor/imgui/imgui.h
        Vendor/imgui/imgui.cpp
        Vendor/imgui/imgui_demo.cpp
        Vendor/imgui/imgui_draw.cpp
        Vendor/imgui/imgui_tables.cpp
        Vendor/imgui/imgui_widgets.cpp
        Vendor/backends/imgui_impl_glfw.cpp
        Vendor/backends/imgui_impl_opengl3.cpp
)

add_executable(Client main.cpp Client.cpp Client.h Includes.h Card.cpp Card.h Resources.h Graphics.cpp Graphics.h Room.h)
target_link_libraries(Client -lglut -lglfw -lGLEW -lGL -lGLU imgui)

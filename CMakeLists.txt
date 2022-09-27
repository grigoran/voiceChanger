cmake_minimum_required(VERSION 3.24)
project(voiceChanger)

set(CMAKE_DEBUG_POSTFIX d)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(portaudio REQUIRED)
include_directories("./headers")
set(SOURCE fft.cpp PaCallback.cpp Sound.cpp Source.cpp)
add_executable(app ${SOURCE})
set_target_properties(app PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
add_subdirectory(sfmlgui)
target_link_libraries(app gui portaudio)

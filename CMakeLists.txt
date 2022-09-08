cmake_minimum_required(VERSION 3.24)

project(voiceChanger)
find_package(portaudio REQUIRED)
include_directories("./headers")
set(SOURCE fft.cpp PaCallback.cpp Sound.cpp Source.cpp)
add_executable(app ${SOURCE})
target_link_libraries(app portaudio)
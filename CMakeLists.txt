cmake_minimum_required(VERSION 3.20)
project(SmartArrayApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG main # Important: Specify a version or a commit hash here.
)
FetchContent_MakeAvailable(ftxui)

add_library(SmartArray INTERFACE)

add_library(CarLib
        src/app/Car.cpp
        src/app/Car.h
        src/app/CarManager.cpp
        src/app/CarManager.h
)
target_link_libraries(CarLib SmartArray)

add_executable(SmartArrayApp
        src/app/main.cpp
        src/app/CarMenu.cpp
        src/app/CarMenu.h
)
target_link_libraries(SmartArrayApp ftxui::screen ftxui::component SmartArray CarLib)
target_include_directories(SmartArrayApp PRIVATE src)

add_subdirectory(tests)
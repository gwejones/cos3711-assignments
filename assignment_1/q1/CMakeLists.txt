cmake_minimum_required(VERSION 3.16)

project(q1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(q1
    main.cpp
)

target_link_libraries(q1 PRIVATE Qt6::Core)

install(TARGETS q1
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

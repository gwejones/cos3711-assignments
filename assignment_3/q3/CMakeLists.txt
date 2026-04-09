cmake_minimum_required(VERSION 3.16)

project(q3 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(q3
    StudentRecordsWindow.cpp
    StudentRecordsWindow.h
    main.cpp
)

target_link_libraries(q3 PRIVATE Qt6::Widgets)

install(TARGETS q3
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

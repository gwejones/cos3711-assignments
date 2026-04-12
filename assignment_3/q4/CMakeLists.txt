cmake_minimum_required(VERSION 3.16)

project(q4 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(q4
    Student.cpp
    Student.h
    StudentList.cpp
    StudentList.h
    StudentListXmlSchema.h
    StudentRecordsWindow.cpp
    StudentRecordsWindow.h
    main.cpp
)

target_link_libraries(q4 PRIVATE Qt6::Widgets)

install(TARGETS q4
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

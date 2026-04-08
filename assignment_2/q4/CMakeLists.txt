cmake_minimum_required(VERSION 3.16)

project(q4 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Xml)

qt_standard_project_setup()

qt_add_executable(q4
    main.cpp
    Shape.cpp
    Shape.h
    Shape1Property.cpp
    Shape1Property.h
    Shape2Property.cpp
    Shape2Property.h
    Circle.cpp
    Circle.h
    Square.cpp
    Square.h
    Ellipse.cpp
    Ellipse.h
    Rectangle.cpp
    Rectangle.h
    ShapeList.cpp
    ShapeList.h
    ShapeFactory.cpp
    ShapeFactory.h
    ShapeXmlSerializer.cpp
    ShapeXmlSerializer.h
    DrawingCanvas.cpp
    DrawingCanvas.h
    ShapesWindow.cpp
    ShapesWindow.h
)

target_link_libraries(q4 PRIVATE Qt6::Widgets Qt6::Xml)

install(TARGETS q4
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

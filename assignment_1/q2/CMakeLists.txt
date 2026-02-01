cmake_minimum_required(VERSION 3.16)

project(q2 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(q2
    main.cpp
    Vehicle.cpp
    Vehicle.h
    PassengerVehicle.cpp
    PassengerVehicle.h
    TransportVehicle.cpp
    TransportVehicle.h
    VehicleList.cpp
    VehicleList.h
)

target_link_libraries(q2 PRIVATE Qt6::Core)

install(TARGETS q2
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

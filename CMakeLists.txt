cmake_minimum_required(VERSION 3.20.2)
project(TrabalhoDA1)

set(CMAKE_CXX_STANDARD 14)

add_executable(TrabalhoDA1 main.cpp src/Interface/System.h src/Interface/System.cpp
        src/Controller.cpp src/Controller.h src/Interface/Menu.h src/Interface/Menu.cpp
        src/Interface/DirectionsMenu.h src/Interface/DirectionsMenu.cpp src/Interface/OptionsMenu.h
        src/Interface/OptionsMenu.cpp src/Order.h src/Order.cpp src/Truck.h src/Truck.cpp)

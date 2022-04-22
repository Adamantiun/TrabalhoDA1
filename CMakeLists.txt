cmake_minimum_required(VERSION 3.20.2)
project(TrabalhoDA1)

set(CMAKE_CXX_STANDARD 14)

add_executable(TrabalhoDA1 codigo/main.cpp codigo/Interface/System.h codigo/Interface/System.cpp
        codigo/Controller.cpp codigo/Controller.h codigo/Interface/Menu.h codigo/Interface/Menu.cpp
        codigo/Order.h codigo/Order.cpp codigo/Truck.h codigo/Truck.cpp)

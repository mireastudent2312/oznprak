cmake_minimum_required(VERSION 3.26)
project(oznprak)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

find_package(OpenMP REQUIRED)
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
add_executable(oznprak main.cpp Matrix.hpp nn/Layer.hpp nn/Layer.cpp nn/NeuralNetwork.hpp nn/NeuralNetwork.cpp Matrix.cpp nn/NeuralNetwork.cpp nn/ActivationFunction.hpp nn/Sigmoid.hpp nn/Sigmoid.cpp nn/Relu.cpp ui/Window.hpp ui/Window.cpp ui/DrawingScene.cpp ui/DrawingScene.hpp ui/DrawingArea.cpp ui/DrawingArea.hpp Logic.cpp Logic.hpp nn/Softmax.cpp nn/Softmax.hpp)
target_link_libraries(oznprak OpenMP::OpenMP_CXX)
target_link_libraries(oznprak Qt6::Core Qt6::Gui Qt6::Widgets)
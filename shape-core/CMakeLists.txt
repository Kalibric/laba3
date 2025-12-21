cmake_minimum_required(VERSION 3.16)
project(shape-core LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
# Ищем необходимые модули Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Gui)

add_library(shape-core SHARED
    shape.cpp
    shape.h
    groupshape.cpp
    groupshape.h
    shapefactory.h
    shapefactory.cpp
    shape_global.h
    IShapePlugin.h
    shapeloader.h shapeloader.cpp
    pluginloader.h pluginloader.cpp

)

target_compile_definitions(shape-core PRIVATE SHAPE_CORE_LIBRARY)

# Линкуем с Qt Gui (даёт доступ к QPainter)
target_link_libraries(shape-core
    PRIVATE Qt6::Core Qt6::Gui
)

# Даём доступ к инклудам shape-core
target_include_directories(shape-core
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

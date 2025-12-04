cmake_minimum_required(VERSION 3.16)
project(circle-plugin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)       # 👈 ОБЯЗАТЕЛЬНО!

find_package(Qt6 REQUIRED COMPONENTS Core Gui)

add_library(circle-plugin SHARED
    circle.cpp
    circle.h
    circleplugin.cpp
    circleplugin.h
)

# Пути к shape-core
set(SHAPE_CORE_INCLUDE_DIR
    ${CMAKE_SOURCE_DIR}/../shape-core
)

set(SHAPE_CORE_LIB_DIR
    ${CMAKE_SOURCE_DIR}/../shape-core/build/Desktop_Qt_6_9_3_MinGW_64_bit-Debug
)

set(SHAPE_CORE_LIB
    ${SHAPE_CORE_LIB_DIR}/libshape-core.dll.a
)

# include-директория shape-core
target_include_directories(circle-plugin PRIVATE
    ${SHAPE_CORE_INCLUDE_DIR}
)

# Линковка с импорт-библиотекой, а не CMake target'ом
target_link_libraries(circle-plugin PRIVATE
    ${SHAPE_CORE_LIB}
    Qt6::Core
    Qt6::Gui
)

target_include_directories(circle-plugin PRIVATE
    ../shape-core
)

# Копируем DLL рядом с плагином
add_custom_command(TARGET circle-plugin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHAPE_CORE_LIB_DIR}/libshape-core.dll
        $<TARGET_FILE_DIR:circle-plugin>
)

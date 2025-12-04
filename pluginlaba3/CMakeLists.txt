cmake_minimum_required(VERSION 3.16)

project(pluginlaba3 VERSION 0.1 LANGUAGES CXX)

# Автоматическая обработка Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

# ----------------------------
# Источники проекта
# ----------------------------
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    shapestorage.h
    shapestorage.cpp
    paintwidget.h
    paintwidget.cpp
    command.h
    command.cpp
)

# ----------------------------
# Создаём исполняемый файл
# ----------------------------
qt_add_executable(pluginlaba3
    ${PROJECT_SOURCES}
)
# ----------------------------
# Include директории проекта
# ----------------------------
target_include_directories(pluginlaba3
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}        # текущая папка с paintwidget.h, mainwindow.h и др.
        E:/OOP/shape/shape-core            # папка с shape-core
)
# ----------------------------
# Include директории shape-core
# ----------------------------
target_include_directories(pluginlaba3 PRIVATE
    E:/OOP/shape/shape-core   # путь к заголовкам shape-core
)

# ----------------------------
# Путь к DLL и импортной библиотеке
# ----------------------------
set(SHAPE_CORE_LIB_DIR "E:/OOP/shape/shape-core/build/Desktop_Qt_6_9_3_MinGW_64_bit-Debug")

target_link_libraries(pluginlaba3 PRIVATE
    Qt6::Widgets
    "${SHAPE_CORE_LIB_DIR}/libshape-core.dll.a"  # линковка с DLL импортной библиотекой
)

# ----------------------------
# Копирование DLL рядом с exe
# ----------------------------
add_custom_command(TARGET pluginlaba3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SHAPE_CORE_LIB_DIR}/libshape-core.dll"
        $<TARGET_FILE_DIR:pluginlaba3>
)

# ----------------------------
# Установка (опционально)
# ----------------------------
include(GNUInstallDirs)
install(TARGETS pluginlaba3
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

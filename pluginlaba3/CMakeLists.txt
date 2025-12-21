cmake_minimum_required(VERSION 3.16)

project(pluginlaba3 VERSION 0.1 LANGUAGES CXX)

# �������������� ��������� Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# ----------------------------
# ��������� �������
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
# ������� ����������� ����
# ----------------------------
qt_add_executable(pluginlaba3
    ${PROJECT_SOURCES}
    shapetree.h shapetree.cpp
    uniarrow.h uniarrow.cpp
    arrowstorage.h arrowstorage.cpp
    arrow.h arrow.cpp
    biarrow.h biarrow.cpp
    propertywindow.h propertywindow.cpp

)
# ----------------------------
# Include ���������� �������
# ----------------------------
target_include_directories(pluginlaba3
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}        # ������� ����� � paintwidget.h, mainwindow.h � ��.
        ../shape-core            # ����� � shape-core
)
# ----------------------------
# Include ���������� shape-core
# ----------------------------
target_include_directories(pluginlaba3 PRIVATE
    ../shape-core   # ���� � ���������� shape-core
)

# ----------------------------
# ���� � DLL � ��������� ����������
# ----------------------------
set(SHAPE_CORE_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../shape-core/build/Desktop_Qt_6_9_3_MinGW_64_bit-Debug")

target_link_libraries(pluginlaba3 PRIVATE
    Qt6::Widgets
    "${SHAPE_CORE_LIB_DIR}/libshape-core.dll.a"  # �������� � DLL ��������� �����������
)
target_link_libraries(pluginlaba3 PRIVATE Qt6::Widgets)
target_link_libraries(pluginlaba3 PRIVATE Qt6::Widgets)

# ----------------------------
# ����������� DLL ����� � exe
# ----------------------------
add_custom_command(TARGET pluginlaba3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SHAPE_CORE_LIB_DIR}/libshape-core.dll"
        $<TARGET_FILE_DIR:pluginlaba3>
)

# ----------------------------
# ��������� (�����������)
# ----------------------------
include(GNUInstallDirs)
install(TARGETS pluginlaba3
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

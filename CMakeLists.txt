cmake_minimum_required(VERSION 3.16)
project(qforensics-cxx LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    
else()
    find_path(TSK_INCLUDE_DIR NAMES tsk/libtsk.h
        PATHS /opt/homebrew/include /usr/local/include
    )

    find_library(TSK_LIBRARY NAMES tsk
        PATHS /opt/homebrew/lib /usr/local/lib
    )
endif()


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()


file(GLOB WIDGET_SOURCES 
    CONFIGURE_DEPENDS
    "widgets/*.cpp"
    "widgets/*.c"
    "widgets/*.h"
)

set(PROJECT_SOURCES
    main.cpp
    MainWindow.ui
    MainWindow.h
    MainWindow.cpp
    ${WIDGET_SOURCES}
)

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

target_include_directories(${PROJECT_NAME} PRIVATE ${TSK_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${TSK_LIBRARY})

cmake_minimum_required(VERSION 3.0.0)
project(qt-smallboy VERSION 0.1.0 LANGUAGES C CXX)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
# ----------

include(CTest)
enable_testing()

find_package(Qt5 REQUIRED COMPONENTS Widgets)


add_executable(qt-smallboy main.cpp mainwindow.h mainwindow.cpp mainwindow.ui resources.qrc)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(qt-smallboy Qt5::Widgets)
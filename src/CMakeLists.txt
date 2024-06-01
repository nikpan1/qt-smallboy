cmake_minimum_required(VERSION 3.0.0)
project(qt-smallboy VERSION 0.1.0 LANGUAGES C CXX)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# ----------

find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt5 COMPONENTS Core Network REQUIRED)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# ----------

set(SOURCES
 main.cpp mainwindow.h mainwindow.cpp mainwindow.ui 
 Player/Playerwidget.h Player/Playerwidget.cpp Player/Player.h Player/Player.cpp 
 Networking/Server.h Networking/Server.cpp Networking/Client.h Networking/Client.cpp 
 Json/JsonHandler.cpp Json/JsonHandler.h 
 Debug.h)

add_executable(qt-smallboy ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(qt-smallboy Qt5::Widgets Qt5::Core Qt5::Network)

enable_testing()
add_test(NAME runTests COMMAND runTests)

# Add clang-format target
find_program(CLANG_FORMAT_BIN clang-format)
if (CLANG_FORMAT_BIN)
    add_custom_target(
        format
        COMMAND ${CLANG_FORMAT_BIN} -i ${SOURCES}
        COMMENT "Running clang-format on source files"
    )
endif()
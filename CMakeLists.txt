cmake_minimum_required(VERSION 3.23)

# Remove when sharing with others.
list(APPEND CMAKE_PREFIX_PATH "/home/zb_bamboo/DEV/__NEW__/CPP/Qt_Plugins/plugins")

project(Rz_read_metadata
  VERSION 0.01.0
      DESCRIPTION "Plugin to read/write photo metadata"
      HOMEPAGE_URL "https://github.com/Zheng-Bote/qt_metadata_desktop"
      LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROG_EXEC_NAME "${PROJECT_NAME}")
set(PROG_NAME "Photos to Gallery")
set(PROG_VERSION "${PROJECT_VERSION}")
set(PROG_HOMEPAGE "${PROJECT_HOMEPAGE_URL}")
set(PROG_DESCRIPTION "${PROJECT_DESCRIPTION}")
set(PROG_ORGANIZATION_NAME "ZHENG Robert")
set(PROG_ORGANIZATION_DOMAIN "net.hase-zheng")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(CMAKE_CXX_COMPILER clang++)
endif()

configure_file("${CMAKE_SOURCE_DIR}/configure/rz_config.h.in"
               "${CMAKE_SOURCE_DIR}/includes/rz_config.h")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)


add_library(
  rz_read_metadata SHARED
  rz_read_metadata.cpp
  rz_read_metadata.hpp
  includes/rz_photo-gallery_plugins.hpp)

target_link_libraries(rz_read_metadata
                      PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(rz_read_metadata
                           PRIVATE RZ_READ_METADATA_LIBRARY)

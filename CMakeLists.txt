cmake_minimum_required(VERSION 3.16)
project(shore-backend-wxwidgets VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

find_package(shore CONFIG REQUIRED)
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_library(shore_backend_wxwidgets src/wx_backend.cpp)
add_library(shore-backend-wxwidgets::shore-backend-wxwidgets ALIAS shore_backend_wxwidgets)
set_target_properties(shore_backend_wxwidgets PROPERTIES EXPORT_NAME shore-backend-wxwidgets)
target_include_directories(shore_backend_wxwidgets
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE src
)
target_link_libraries(shore_backend_wxwidgets PUBLIC shore::shore ${wxWidgets_LIBRARIES})

install(TARGETS shore_backend_wxwidgets EXPORT shoreBackendWxWidgetsTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT shoreBackendWxWidgetsTargets
  FILE shoreBackendWxWidgetsTargets.cmake
  NAMESPACE shore-backend-wxwidgets::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/shore-backend-wxwidgets
)

configure_package_config_file(
  cmake/shore-backend-wxwidgetsConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/shore-backend-wxwidgetsConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/shore-backend-wxwidgets
)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/shore-backend-wxwidgetsConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/shore-backend-wxwidgetsConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/shore-backend-wxwidgetsConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/shore-backend-wxwidgets
)

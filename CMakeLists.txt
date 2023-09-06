##############################################################################
# Project
##############################################################################

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(maliput_py LANGUAGES C CXX VERSION 0.1.6)

##############################################################################
# Find 3rd Party Packages
##############################################################################

message(STATUS "\n\n====== Finding 3rd Party Packages ======\n")

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(maliput REQUIRED)

# call pybind11-config to obtain the root of the cmake package
execute_process(COMMAND ${PYTHON_EXECUTABLE} -m pybind11 --cmakedir
                OUTPUT_VARIABLE pybind11_ROOT_RAW)
string(STRIP ${pybind11_ROOT_RAW} pybind11_ROOT)
set(pybind11_DIR ${pybind11_ROOT})
find_package(pybind11)

##############################################################################
# Project Configuration
##############################################################################

message(STATUS "\n\n========= Project Configuration ========\n")

set(BUILD_SHARED_LIBS true)

include(${PROJECT_SOURCE_DIR}/cmake/DefaultCFlags.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/SanitizersConfig.cmake)
include(FetchContent)

ament_python_install_package("maliput")

ament_environment_hooks(
  "${ament_cmake_package_templates_ENVIRONMENT_HOOK_LIBRARY_PATH}"
)

##############################################################################
# Wheel
##############################################################################

if (WHEEL_GENERATION)
  message(STATUS "Wheel generation - Enabled")
  FetchContent_Declare(python-cmake-wheel
  GIT_REPOSITORY "https://github.com/francocipollone/python-cmake-wheel"
  GIT_TAG        "francocipollone/python_lib"
  GIT_SHALLOW    ON)

  FetchContent_GetProperties(python-cmake-wheel)
  FetchContent_MakeAvailable(python-cmake-wheel)
  list(APPEND CMAKE_MODULE_PATH "${python-cmake-wheel_SOURCE_DIR}")
  include(python-wheel)
  set(WHEEL_DEPLOY_DIRECTORY "${CMAKE_BINARY_DIR}/wheel")
else()
  message(STATUS "Wheel generation - Disabled")
endif()

##############################################################################
# Sources
##############################################################################
add_subdirectory(src)

##############################################################################
# Tests
##############################################################################

if(BUILD_TESTING)
  find_package(ament_cmake_clang_format REQUIRED)
  find_package(ament_cmake_flake8 REQUIRED)
  enable_testing()
  add_subdirectory(test)
  ament_flake8("--config" ${CMAKE_CURRENT_SOURCE_DIR}/.flake8)
  ament_clang_format(CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/.clang-format)
endif()

##############################################################################
# Docs
##############################################################################

if(BUILD_DOCS)
  message(STATUS "Doxygen generation - Enabled")
  find_package(ament_cmake_doxygen REQUIRED)
  ament_doxygen_generate(doxygen_maliput_py
    CONFIG_OVERLAY doc/Doxyfile.overlay.in
    DEPENDENCIES maliput
    TEST_ON_WARNS
  )
  add_definitions(-DBUILD_DOCS)
else()
  message(STATUS "Doxygen generation - Disabled")
endif()

##############################################################################
# Export
##############################################################################

ament_export_dependencies(ament_cmake)
ament_package()

##############################################################################
# Sources
##############################################################################

# api module
pybind11_add_module(api_py
  api_py.cc
  api_rules_py.cc
)

set_target_properties(api_py PROPERTIES OUTPUT_NAME "api")

target_include_directories(api_py
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(api_py
  PRIVATE
    maliput::api
    pybind11::module
)

# math module
pybind11_add_module(math_py math_py.cc)

set_target_properties(math_py PROPERTIES OUTPUT_NAME "math")

target_include_directories(math_py
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(math_py
  PRIVATE
    maliput::math
    pybind11::module
)

# plugin module
pybind11_add_module(plugin_py plugin_py.cc)

set_target_properties(plugin_py PROPERTIES OUTPUT_NAME "plugin")

target_include_directories(plugin_py
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(plugin_py
  PRIVATE
    maliput::plugin
    pybind11::module
)

# utility module
pybind11_add_module(utility_py utility_py.cc)

set_target_properties(utility_py PROPERTIES OUTPUT_NAME "utility")

target_include_directories(utility_py
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(utility_py
  PRIVATE
    maliput::utility
    pybind11::module
)

##############################################################################
# Install
##############################################################################

install(TARGETS api_py
  DESTINATION "${PYTHON_INSTALL_DIR}/maliput"
)

install(TARGETS math_py
  DESTINATION "${PYTHON_INSTALL_DIR}/maliput"
)

install(TARGETS plugin_py
  DESTINATION "${PYTHON_INSTALL_DIR}/maliput"
)

install(TARGETS utility_py
  DESTINATION "${PYTHON_INSTALL_DIR}/maliput"
)

if(WHEEL_GENERATION)
  set(DEPLOY_FILES "${PROJECT_SOURCE_DIR}/maliput/__init__.py")

  add_wheel(api_py math_py plugin_py utility_py
    NAME maliput
    AUTHOR "Franco Cipollone"
    URL "https://github.com/maliput/maliput_py"
    VERSION "${PROJECT_VERSION}"
    DESCRIPTION "Python bindings for the maliput library."
    TARGET_DEPENDENCIES math_py plugin_py utility_py
    # TARGET_DEPENDENCIES math_py plugin_py utility_py maliput::plugin maliput::api maliput::common maliput::math maliput::utility
    LICENSE_PATH "${PROJECT_SOURCE_DIR}/LICENSE"
    DEPLOY_FILES ${DEPLOY_FILES}
  )
endif()

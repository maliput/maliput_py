##############################################################################
# Test helper module
##############################################################################

# Test-only extension module that owns C++ maliput objects and hands out
# PyCapsules to them. Deliberately NOT installed: it exists only in the build
# tree, which is why the pytest below extends PYTHONPATH to find it.
pybind11_add_module(interop_test_helper interop_test_helper.cc)

target_link_libraries(interop_test_helper
  PRIVATE
    maliput::api
    maliput::test_utilities
    pybind11::module
)

##############################################################################
# Tests
##############################################################################

# TODO(francocipollone): Improve this check by wrapping ament_add_pytest_test() function.
# When sanitizers are activated python scripts are disabled.
if (NOT ${SANITIZERS})
  ament_add_pytest_test(interop_pytest
    interop_test.py
    # Avoid pytest from importing the module stub
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    # interop_test_helper lives in the build tree only.
    APPEND_ENV PYTHONPATH=${CMAKE_CURRENT_BINARY_DIR}
  )
endif()

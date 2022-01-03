#pragma once

#include <pybind11/pybind11.h>

namespace maliput {
namespace api {
namespace bindings {

// Loads the bindings for the maliput::api::rules namespace.
//
// @param m A pointer to a pybind11 module already initialized as a submodule of
//        the maliput.api Python module.
void InitializeRulesNamespace(pybind11::module* m);

}  // namespace bindings
}  // namespace api
}  // namespace maliput

// BSD 3-Clause License
//
// Copyright (c) 2022, Woven Planet. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include "bindings/api_interop.h"

#include <cstring>
#include <stdexcept>
#include <string>

#include <maliput/api/road_geometry.h>
#include <maliput/api/road_network.h>

namespace maliput {
namespace bindings {
namespace interop {

namespace py = pybind11;

py::object RoadNetworkFromCapsule(py::capsule capsule, py::object owner) {
  const char* name = capsule.name();
  if (name == nullptr || std::strcmp(name, kRoadNetworkCapsuleName) != 0) {
    throw std::invalid_argument("Expected a PyCapsule named \"" + std::string(kRoadNetworkCapsuleName) + "\", got \"" +
                                std::string(name ? name : "(null)") + "\"");
  }
  auto* ptr = static_cast<api::RoadNetwork*>(capsule);
  if (ptr == nullptr) {
    throw std::invalid_argument("Capsule contains a null pointer");
  }
  return py::cast(ptr, py::return_value_policy::reference_internal, owner);
}

py::object RoadGeometryFromCapsule(py::capsule capsule, py::object owner) {
  const char* name = capsule.name();
  if (name == nullptr || std::strcmp(name, kRoadGeometryCapsuleName) != 0) {
    throw std::invalid_argument("Expected a PyCapsule named \"" + std::string(kRoadGeometryCapsuleName) + "\", got \"" +
                                std::string(name ? name : "(null)") + "\"");
  }
  const auto* ptr = static_cast<const api::RoadGeometry*>(capsule);
  if (ptr == nullptr) {
    throw std::invalid_argument("Capsule contains a null pointer");
  }
  return py::cast(ptr, py::return_value_policy::reference_internal, owner);
}

}  // namespace interop
}  // namespace bindings
}  // namespace maliput

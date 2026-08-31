// BSD 3-Clause License
//
// Copyright (c) 2026, Woven Planet. All rights reserved.
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
#pragma once

#include <pybind11/pybind11.h>

namespace maliput {
namespace bindings {
namespace interop {

// PyCapsule names that external consumers must use when constructing capsules.
constexpr const char* kRoadNetworkCapsuleName = "maliput.api.RoadNetwork";
constexpr const char* kRoadGeometryCapsuleName = "maliput.api.RoadGeometry";

// Wrap a raw const maliput::api::RoadNetwork* (passed via PyCapsule) as a
// Python object. The returned object's lifetime is tied to `owner` via
// pybind11's reference_internal policy.
//
// Requires that the pybind11 type for maliput::api::RoadNetwork has already
// been registered (i.e. the `api` module is loaded).
pybind11::object RoadNetworkFromCapsule(pybind11::capsule capsule, pybind11::object owner);

// Wrap a raw const maliput::api::RoadGeometry* (passed via PyCapsule) as a
// Python object. Same lifetime semantics as RoadNetworkFromCapsule.
pybind11::object RoadGeometryFromCapsule(pybind11::capsule capsule, pybind11::object owner);

}  // namespace interop
}  // namespace bindings
}  // namespace maliput

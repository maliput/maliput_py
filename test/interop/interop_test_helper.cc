// BSD 3-Clause License
//
// Copyright (c) 2026, Woven by Toyota
// All rights reserved.
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

// Test-only helper extension module for exercising the `from_capsule` interop
// API from Python. It stands in for an external consumer (e.g. Rust/PyO3
// bindings) that owns maliput objects on the C++ side and hands out raw
// pointers via PyCapsule.
//
// This module deliberately registers NO maliput types: pybind11's type registry
// is process-global, so declaring e.g. py::class_<api::RoadNetwork> here would
// collide with maliput.api ("generic_type: type is already registered") as soon
// as both modules are imported. The bindings under test live in maliput.api;
// this module only produces capsules and reference values to assert against.
#include <memory>
#include <string>

#include <maliput/api/road_geometry.h>
#include <maliput/api/road_network.h>
#include <maliput/test_utilities/mock.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace {

// PyCapsule names that maliput's from_capsule() implementations require. Kept
// as literals rather than including bindings/api_interop.h so that a typo in
// the shipped constants is caught by these tests instead of being mirrored.
constexpr const char* kRoadNetworkCapsuleName = "maliput.api.RoadNetwork";
constexpr const char* kRoadGeometryCapsuleName = "maliput.api.RoadGeometry";

// Owns a RoadNetwork on the C++ side and vends PyCapsules pointing into it.
// Instances of this class serve as the `owner` argument to from_capsule().
class RoadNetworkOwner {
 public:
  RoadNetworkOwner() : road_network_(maliput::api::test::CreateRoadNetwork()) {}

  py::capsule road_network_capsule() const { return py::capsule(road_network_.get(), kRoadNetworkCapsuleName); }

  py::capsule road_geometry_capsule() const {
    // from_capsule() takes ownership of nothing; the const_cast only satisfies
    // PyCapsule's void* signature.
    return py::capsule(const_cast<maliput::api::RoadGeometry*>(road_network_->road_geometry()),
                       kRoadGeometryCapsuleName);
  }

  // Negative-test fixture: valid pointer, wrong capsule name.
  py::capsule misnamed_capsule() const { return py::capsule(road_network_.get(), "not.a.maliput.type"); }

  // Negative-test fixture: valid pointer, no capsule name at all.
  py::capsule unnamed_capsule() const {
    return py::reinterpret_steal<py::capsule>(PyCapsule_New(road_network_.get(), nullptr, nullptr));
  }

  // Reference values, read straight from the C++ objects, for the Python side
  // to compare the wrapped objects against.
  std::string road_geometry_id() const { return road_network_->road_geometry()->id().string(); }
  int num_junctions() const { return road_network_->road_geometry()->num_junctions(); }
  int num_branch_points() const { return road_network_->road_geometry()->num_branch_points(); }

 private:
  std::unique_ptr<maliput::api::RoadNetwork> road_network_;
};

// NOTE: there is deliberately no null-pointer fixture here. CPython's
// PyCapsule_New() rejects a null pointer outright (ValueError: "PyCapsule_New
// called with null pointer"), and PyCapsule_SetPointer() rejects it too, so a
// capsule holding nullptr cannot be constructed. The nullptr guards in
// api_interop.cc are therefore not reachable from Python.

}  // namespace

PYBIND11_MODULE(interop_test_helper, m) {
  m.doc() = "Test-only helper that produces PyCapsules wrapping C++-owned maliput objects.";

  py::class_<RoadNetworkOwner>(m, "RoadNetworkOwner")
      .def(py::init<>())
      .def("road_network_capsule", &RoadNetworkOwner::road_network_capsule)
      .def("road_geometry_capsule", &RoadNetworkOwner::road_geometry_capsule)
      .def("misnamed_capsule", &RoadNetworkOwner::misnamed_capsule)
      .def("unnamed_capsule", &RoadNetworkOwner::unnamed_capsule)
      .def("road_geometry_id", &RoadNetworkOwner::road_geometry_id)
      .def("num_junctions", &RoadNetworkOwner::num_junctions)
      .def("num_branch_points", &RoadNetworkOwner::num_branch_points);
}

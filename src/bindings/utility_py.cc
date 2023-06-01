// BSD 3-Clause License
//
// Copyright (c) 2023, Woven Planet. All rights reserved.
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
#include <string>

#include <maliput/utility/generate_obj.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace maliput {
namespace bindings {

namespace py = pybind11;

PYBIND11_MODULE(utility, m) {
  py::class_<utility::ObjFeatures>(m, "ObjFeatures")
      .def(py::init<>())
      .def_readwrite("max_grid_unit", &utility::ObjFeatures::max_grid_unit)
      .def_readwrite("min_grid_resolution", &utility::ObjFeatures::min_grid_resolution)
      .def_readwrite("draw_stripes", &utility::ObjFeatures::draw_stripes)
      .def_readwrite("draw_arrows", &utility::ObjFeatures::draw_arrows)
      .def_readwrite("draw_lane_haze", &utility::ObjFeatures::draw_lane_haze)
      .def_readwrite("draw_branch_points", &utility::ObjFeatures::draw_branch_points)
      .def_readwrite("draw_elevation_bounds", &utility::ObjFeatures::draw_elevation_bounds)
      .def_readwrite("off_grid_mesh_generation", &utility::ObjFeatures::off_grid_mesh_generation)
      .def_readwrite("simplify_mesh_threshold", &utility::ObjFeatures::simplify_mesh_threshold)
      .def_readwrite("stripe_width", &utility::ObjFeatures::stripe_width)
      .def_readwrite("stripe_elevation", &utility::ObjFeatures::stripe_elevation)
      .def_readwrite("arrow_elevation", &utility::ObjFeatures::arrow_elevation)
      .def_readwrite("lane_haze_elevation", &utility::ObjFeatures::lane_haze_elevation)
      .def_readwrite("branch_point_elevation", &utility::ObjFeatures::branch_point_elevation)
      .def_readwrite("branch_point_height", &utility::ObjFeatures::branch_point_height)
      .def_readwrite("origin", &utility::ObjFeatures::origin)
      .def_readwrite("highlighted_segments", &utility::ObjFeatures::highlighted_segments);

  m.def("GenerateObjFile",
        py::overload_cast<const api::RoadNetwork*, const std::string&, const std::string&, const utility::ObjFeatures&>(
            &maliput::utility::GenerateObjFile),
        "Generates a Wavefront OBJ model of the road surface of an maliput::api::RoadNetwork.", py::arg("road_network"),
        py::arg("dirpath"), py::arg("fileroot"), py::arg("features"));
}

}  // namespace bindings
}  // namespace maliput

// BSD 3-Clause License
//
// Copyright (c) 2022, Woven Planet. All rights reserved.
// Copyright (c) 2021-2022, Toyota Research Institute. All rights reserved.
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

/// @file maliput_python_interface.h
/// @page maliput_python_interface Maliput Python Interface
/// @date October 21, 2021
/// @tableofcontents
///
/// @section maliput_python_interface_section Maliput Python Interface
///
/// @subsection maliput_python_interface_overview Overview
///
/// The `maliput_py` package provides a maliput python interface covering:
///  - maliput::api
///  - maliput::math
///  - maliput::plugin
///
/// Python bindings are created using [pybind11](https://github.com/pybind/pybind11) library.
/// @subsection maliput_api_bindings Maliput api
///
/// `maliput.api` submodule provides bindings to maliput::api entities such as:
/// - maliput::api::InertialPosition
/// - maliput::api::Junction
/// - maliput::api::Lane
/// - maliput::api::LaneId
/// - maliput::api::LanePosition
/// - maliput::api::LanePositionResult
/// - maliput::api::RoadGeometry
/// - maliput::api::RoadGeometry::IdIndex
/// - maliput::api::RoadGeometryId
/// - maliput::api::RoadNetwork
/// - maliput::api::RoadPosition
/// - maliput::api::Rotation
/// - maliput::api::Segment
///
/// Code example:
/// @code{.py}
/// import maliput.api
///
/// inertial_position = maliput.api.InertialPosition(x=1., y=2., z=3.)
/// @endcode
///
/// @subsection maliput_math_bindings Maliput math
///
/// `maliput.math` submodule provides bindings to maliput::math entities such as:
/// - maliput::math::Vector3
/// - maliput::math::Vector4
/// - maliput::math::RollPitchYaw
/// - maliput::math::Quaternion
///
/// Code example:
/// @code{.py}
/// import maliput.math
/// rpy = maliput.math.RollPitchYaw(1.0, 2.0, 3.0)
/// quaternion = rpy.ToQuaternion()
/// @endcode
///
/// @subsection maliput_plugin_bindings Maliput plugin
///
/// `maliput.plugin` submodule provides bindings for the \subpage maliput_plugin_architecture.
///
/// Code example:
/// @code{.py}
/// import maliput.plugin
///
/// manager = maliput.plugin.MaliputPluginManager()
/// # Plugins` id can be listed by doing:
/// plugin_ids = maliput.plugin.MaliputPluginManager().ListPlugins()
/// # A loaded plugin can be obtained by doing:
/// my_plugin = maliput.plugin.MaliputPluginManager().GetPlugin("foo_plugin")
/// @endcode
///
/// There is also provided a method to easily get a maliput::api::RoadNetwork from a maliput::plugin::RoadNetworkLoader
/// implementation.
///
/// Code example:
/// @code{.py}
/// import maliput.api
/// import maliput.plugin
///
/// road_network = maliput.plugin.create_road_network("my_road_network_loader_plugin", dict())
/// num_junctions = road_network.road_geometry().num_junctions()
/// @endcode

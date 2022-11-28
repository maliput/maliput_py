// BSD 3-Clause License
//
// Copyright (c) 2022, Woven Planet. All rights reserved.
// Copyright (c) 2020-2022, Toyota Research Institute. All rights reserved.
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

#include <maliput/plugin/create_road_network.h>
#include <maliput/plugin/maliput_plugin.h>
#include <maliput/plugin/maliput_plugin_manager.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace maliput {
namespace bindings {

namespace py = pybind11;

PYBIND11_MODULE(plugin, m) {
  py::class_<plugin::MaliputPlugin>(m, "MaliputPlugin")
      .def(py::init<std::string>())
      .def("GetId", &plugin::MaliputPlugin::GetId)
      .def("GetType", &plugin::MaliputPlugin::GetType);

  py::class_<plugin::MaliputPluginManager>(m, "MaliputPluginManager")
      .def(py::init<>())
      .def("GetPlugin",
           [](plugin::MaliputPluginManager& self, const std::string& plugin_name) {
             return self.GetPlugin(plugin::MaliputPlugin::Id(plugin_name));
           })
      .def("AddPlugin", &plugin::MaliputPluginManager::AddPlugin)
      .def("ListPlugins", &plugin::MaliputPluginManager::ListPlugins);

  m.def("create_road_network", &maliput::plugin::CreateRoadNetwork,
        "Creates a maliput::api::plugin::RoadNetwork using `plugin_id` implementation.", py::arg("plugin_id"),
        py::arg("properties"));
}

}  // namespace bindings
}  // namespace maliput

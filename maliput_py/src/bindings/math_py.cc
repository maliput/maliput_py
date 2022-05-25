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
#include <sstream>

#include <maliput/math/quaternion.h>
#include <maliput/math/roll_pitch_yaw.h>
#include <maliput/math/vector.h>
#include <pybind11/pybind11.h>

namespace maliput {
namespace bindings {

namespace py = pybind11;

PYBIND11_MODULE(math, m) {
  py::class_<math::Vector3>(m, "Vector3")
      .def(py::init<double, double, double>())
      .def("__getitem__", py::overload_cast<std::size_t>(&math::Vector3::operator[]), py::is_operator())
      .def("__eq__", [](const math::Vector3& a, const math::Vector3& b) { return a == b; })
      .def("__ne__", [](const math::Vector3& a, const math::Vector3& b) { return a != b; })
      .def("__str__",
           [](const math::Vector3& self) {
             std::stringstream ss;
             ss << self;
             return ss.str();
           })
      .def("size", &math::Vector3::size)
      .def("x", py::overload_cast<>(&math::Vector3::x))
      .def("y", py::overload_cast<>(&math::Vector3::y))
      .def("z", py::overload_cast<>(&math::Vector3::z));

  py::class_<math::Vector4>(m, "Vector4")
      .def(py::init<double, double, double, double>())
      .def("__getitem__", py::overload_cast<std::size_t>(&math::Vector4::operator[]), py::is_operator())
      .def("__eq__", [](const math::Vector4& a, const math::Vector4& b) { return a == b; })
      .def("__ne__", [](const math::Vector4& a, const math::Vector4& b) { return a != b; })
      .def("__str__",
           [](const math::Vector4& self) {
             std::stringstream ss;
             ss << self;
             return ss.str();
           })
      .def("size", &math::Vector4::size)
      .def("x", py::overload_cast<>(&math::Vector4::x))
      .def("y", py::overload_cast<>(&math::Vector4::y))
      .def("z", py::overload_cast<>(&math::Vector4::z))
      .def("w", py::overload_cast<>(&math::Vector4::w));

  py::class_<math::RollPitchYaw>(m, "RollPitchYaw")
      .def(py::init<double, double, double>())
      .def("__str__",
           [](const math::RollPitchYaw& self) {
             std::stringstream ss;
             ss << self.vector();
             return ss.str();
           })
      .def("ToQuaternion", &math::RollPitchYaw::ToQuaternion)
      .def("roll_angle", py::overload_cast<>(&math::RollPitchYaw::roll_angle))
      .def("pitch_angle", py::overload_cast<>(&math::RollPitchYaw::pitch_angle))
      .def("yaw_angle", py::overload_cast<>(&math::RollPitchYaw::yaw_angle));

  py::class_<math::Quaternion>(m, "Quaternion")
      .def(py::init<double, double, double, double>())
      .def("__str__",
           [](const math::Quaternion& self) {
             std::stringstream ss;
             ss << self;
             return ss.str();
           })
      .def("coeffs", &math::Quaternion::coeffs)
      .def("w", py::overload_cast<>(&math::Quaternion::w))
      .def("x", py::overload_cast<>(&math::Quaternion::x))
      .def("y", py::overload_cast<>(&math::Quaternion::y))
      .def("z", py::overload_cast<>(&math::Quaternion::z));
}

}  // namespace bindings
}  // namespace maliput

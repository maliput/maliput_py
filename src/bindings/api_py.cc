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
#include <maliput/api/branch_point.h>
#include <maliput/api/intersection.h>
#include <maliput/api/junction.h>
#include <maliput/api/lane.h>
#include <maliput/api/lane_data.h>
#include <maliput/api/regions.h>
#include <maliput/api/road_geometry.h>
#include <maliput/api/road_network.h>
#include <maliput/api/segment.h>
#include <maliput/api/unique_id.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "bindings/api_rules_py.h"

namespace maliput {
namespace bindings {

namespace py = pybind11;

PYBIND11_MODULE(api, m) {
  // TODO(jadecastro) These bindings are work-in-progress. Expose additional
  // Maliput API features, as necessary (see #7918).

  // TODO(m-chaturvedi) Add doc when typedefs are parsed (#9599)
  py::class_<api::RoadGeometryId>(m, "RoadGeometryId")
      .def(py::init<std::string>())
      .def(py::detail::hash(py::self))
      .def("string", &api::RoadGeometryId::string)
      .def("__repr__", &api::RoadGeometryId::string)
      .def("__eq__", &api::RoadGeometryId::operator==);

  py::class_<api::InertialPosition>(m, "InertialPosition")
      .def(py::init<double, double, double>(), py::arg("x"), py::arg("y"), py::arg("z"))
      .def("__eq__", &api::InertialPosition::operator==)
      .def("xyz", &api::InertialPosition::xyz, py::return_value_policy::reference_internal)
      .def("length", &api::InertialPosition::length)
      .def("Distance", &api::InertialPosition::Distance, py::arg("inertial_position"))
      .def("x", &api::InertialPosition::x)
      .def("set_x", &api::InertialPosition::set_x)
      .def("y", &api::InertialPosition::y)
      .def("set_y", &api::InertialPosition::set_y)
      .def("z", &api::InertialPosition::z)
      .def("set_z", &api::InertialPosition::set_z);

  py::class_<api::LanePosition>(m, "LanePosition")
      .def(py::init<double, double, double>(), py::arg("s"), py::arg("r"), py::arg("h"))
      .def("srh", &api::LanePosition::srh, py::return_value_policy::reference_internal)
      .def("s", &api::LanePosition::s)
      .def("set_s", &api::LanePosition::set_s)
      .def("r", &api::LanePosition::r)
      .def("set_r", &api::LanePosition::set_r)
      .def("h", &api::LanePosition::h)
      .def("set_h", &api::LanePosition::set_h);

  py::class_<api::LanePositionResult>(m, "LanePositionResult")
      .def(py::init<>())
      .def(py::init<const api::LanePosition&, const api::InertialPosition&, double>(), py::arg("lane_position"),
           py::arg("nearest_position"), py::arg("distance"))
      .def_readwrite("lane_position", &api::LanePositionResult::lane_position)
      .def_readwrite("nearest_position", &api::LanePositionResult::nearest_position)
      .def_readwrite("distance", &api::LanePositionResult::distance);

  py::class_<api::RoadPosition>(m, "RoadPosition")
      .def(py::init<>())
      .def(py::init<const api::Lane*, const api::LanePosition&>(), py::arg("lane"), py::arg("pos"),
           // Keep alive, reference: `self` keeps `Lane*` alive.
           py::keep_alive<1, 2>())
      .def_readwrite("pos", &api::RoadPosition::pos)
      .def_readonly("lane", &api::RoadPosition::lane)
      .def("ToInertialPosition", &api::RoadPosition::ToInertialPosition);

  py::class_<api::RoadPositionResult>(m, "RoadPositionResult")
      .def(py::init<>())
      .def_readwrite("road_position", &api::RoadPositionResult::road_position)
      .def_readwrite("nearest_position", &api::RoadPositionResult::nearest_position)
      .def_readwrite("distance", &api::RoadPositionResult::distance);

  py::class_<api::Rotation>(m, "Rotation")
      .def(py::init<>())
      .def("quat", &api::Rotation::quat, py::return_value_policy::reference_internal)
      .def("rpy", &api::Rotation::rpy);

  py::class_<api::HBounds>(m, "HBounds")
      .def(py::init<>())
      .def(py::init<double, double>(), py::arg("min_h"), py::arg("max_h"))
      .def("min_h", &api::HBounds::min)
      .def("max_h", &api::HBounds::max)
      .def("set_min_h", &api::HBounds::set_min)
      .def("set_max_h", &api::HBounds::set_max);

  py::class_<api::RBounds>(m, "RBounds")
      .def(py::init<>())
      .def(py::init<double, double>(), py::arg("min_r"), py::arg("max_r"))
      .def("min_r", &api::RBounds::min)
      .def("max_r", &api::RBounds::max)
      .def("set_min_r", &api::RBounds::set_min)
      .def("set_max_r", &api::RBounds::set_max);

  py::class_<api::IsoLaneVelocity>(m, "IsoLaneVelocity")
      .def(py::init<>())
      .def(py::init<double, double, double>(), py::arg("sigma"), py::arg("rho"), py::arg("eta"))
      .def_readwrite("sigma_v", &api::IsoLaneVelocity::sigma_v)
      .def_readwrite("rho_v", &api::IsoLaneVelocity::rho_v)
      .def_readwrite("eta_v", &api::IsoLaneVelocity::eta_v);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
  py::class_<api::RoadNetwork>(m, "RoadNetwork")
      // TODO(https://github.com/maliput/maliput_infrastructure/issues/225): Add constructor binding once it is
      // supported by pybind11.
      .def("road_geometry", &api::RoadNetwork::road_geometry, py::return_value_policy::reference_internal)
      .def("rulebook", &api::RoadNetwork::rulebook, py::return_value_policy::reference_internal)
      .def("traffic_light_book", &api::RoadNetwork::traffic_light_book, py::return_value_policy::reference_internal)
      .def("intersection_book", &api::RoadNetwork::intersection_book, py::return_value_policy::reference_internal)
      .def("phase_ring_book", &api::RoadNetwork::phase_ring_book, py::return_value_policy::reference_internal)
      .def("right_of_way_rule_state_provider", &api::RoadNetwork::right_of_way_rule_state_provider,
           py::return_value_policy::reference_internal)
      .def("phase_provider", &api::RoadNetwork::phase_provider, py::return_value_policy::reference_internal)
      .def("rule_registry", &api::RoadNetwork::rule_registry, py::return_value_policy::reference_internal)
      .def("discrete_value_rule_state_provider", &api::RoadNetwork::discrete_value_rule_state_provider,
           py::return_value_policy::reference_internal)
      .def("range_value_rule_state_provider", &api::RoadNetwork::range_value_rule_state_provider,
           py::return_value_policy::reference_internal)
      .def("Contains", py::overload_cast<const api::RoadPosition&>(&api::RoadNetwork::Contains, py::const_),
           py::arg("road_position"))
      .def("Contains", py::overload_cast<const api::LaneId&>(&api::RoadNetwork::Contains, py::const_),
           py::arg("lane_id"));
#pragma GCC diagnostic pop

  py::class_<api::RoadGeometry>(m, "RoadGeometry")
      .def("id", &api::RoadGeometry::id)
      .def("num_junctions", &api::RoadGeometry::num_junctions)
      .def("junction", &api::RoadGeometry::junction, py::return_value_policy::reference_internal)
      .def("ById", &api::RoadGeometry::ById, py::return_value_policy::reference_internal)
      // clang-format off
      .def("ToRoadPosition",
           [](const api::RoadGeometry& self, const api::InertialPosition& inertial_position) {
             return self.ToRoadPosition(inertial_position);
           }, py::arg("inertial_position"))
      .def("ToRoadPositionByHint",
           [](const api::RoadGeometry& self, const api::InertialPosition& inertial_position,
              const api::RoadPosition& road_position) { return self.ToRoadPosition(inertial_position, road_position); },
           py::arg("inertial_position"), py::arg("hint"))
      // clang-format on
      .def("FindRoadPositions", &api::RoadGeometry::FindRoadPositions, py::arg("inertial_position"), py::arg("radius"));

  py::class_<api::RoadGeometry::IdIndex>(m, "RoadGeometry.IdIndex")
      .def("GetLane", &api::RoadGeometry::IdIndex::GetLane, py::arg("id"), py::return_value_policy::reference_internal)
      .def("GetLanes", &api::RoadGeometry::IdIndex::GetLanes, py::return_value_policy::reference_internal)
      .def("GetSegment", &api::RoadGeometry::IdIndex::GetSegment, py::arg("id"),
           py::return_value_policy::reference_internal)
      .def("GetJunction", &api::RoadGeometry::IdIndex::GetJunction, py::arg("id"),
           py::return_value_policy::reference_internal);

  py::class_<api::JunctionId>(m, "JunctionId")
      .def(py::init<std::string>())
      .def(py::detail::hash(py::self))
      .def("string", &api::JunctionId::string)
      .def("__eq__", &api::JunctionId::operator==)
      .def("__repr__", [](const api::JunctionId& id) { return id.string(); });

  py::class_<api::Junction>(m, "Junction")
      .def("num_segments", &api::Junction::num_segments)
      .def("segment", &api::Junction::segment, py::return_value_policy::reference_internal)
      .def("id", &api::Junction::id, py::return_value_policy::reference_internal)
      .def("road_geometry", &api::Junction::road_geometry, py::return_value_policy::reference_internal);

  py::class_<api::SegmentId>(m, "SegmentId")
      .def(py::init<std::string>())
      .def(py::detail::hash(py::self))
      .def("string", &api::SegmentId::string)
      .def("__eq__", &api::SegmentId::operator==)
      .def("__repr__", [](const api::SegmentId& id) { return id.string(); });

  py::class_<api::Segment>(m, "Segment")
      .def("num_lanes", &api::Segment::num_lanes)
      .def("lane", &api::Segment::lane, py::return_value_policy::reference_internal)
      .def("junction", &api::Segment::num_lanes, py::return_value_policy::reference_internal)
      .def("id", &api::Segment::id, py::return_value_policy::reference_internal);

  py::class_<api::LaneId>(m, "LaneId")
      .def(py::init<std::string>())
      .def(py::detail::hash(py::self))
      .def("string", &api::LaneId::string)
      .def("__eq__", &api::LaneId::operator==)
      .def("__repr__", [](const api::LaneId& id) { return id.string(); });

  py::class_<api::Lane>(m, "Lane")
      .def("id", &api::Lane::id)
      .def("segment", &api::Lane::segment, py::return_value_policy::reference_internal)
      .def("index", &api::Lane::index)
      .def("to_left", &api::Lane::to_left, py::return_value_policy::reference_internal)
      .def("to_right", &api::Lane::to_right, py::return_value_policy::reference_internal)
      .def("length", &api::Lane::length)
      .def("lane_bounds", &api::Lane::lane_bounds, py::arg("s"))
      .def("segment_bounds", &api::Lane::segment_bounds, py::arg("s"))
      .def("elevation_bounds", &api::Lane::elevation_bounds, py::arg("s"), py::arg("r"))
      .def("ToInertialPosition", &api::Lane::ToInertialPosition)
      .def("ToLanePosition", &api::Lane::ToLanePosition)
      .def("ToSegmentPosition", &api::Lane::ToSegmentPosition)
      .def("GetOrientation", &api::Lane::GetOrientation)
      .def("EvalMotionDerivatives", &api::Lane::EvalMotionDerivatives, py::arg("lane_postion"), py::arg("velocity"))
      .def("GetBranchPoint", &api::Lane::GetBranchPoint, py::arg("which_end"))
      .def("GetConfluentBranches", &api::Lane::GetConfluentBranches, py::arg("which_end"),
           py::return_value_policy::reference_internal)
      .def("GetOngoingBranches", &api::Lane::GetOngoingBranches, py::arg("which_end"),
           py::return_value_policy::reference_internal)
      .def("GetDefaultBranch", &api::Lane::GetDefaultBranch, py::arg("which_end"),
           py::return_value_policy::reference_internal)
      .def("Contains", &api::Lane::Contains, py::arg("lane_position"));

  py::class_<api::SRange>(m, "SRange")
      .def(py::init<double, double>(), py::arg("s0"), py::arg("s1"))
      .def("s0", &api::SRange::s0)
      .def("s1", &api::SRange::s1)
      .def("set_s0", &api::SRange::set_s0, py::arg("s0"))
      .def("set_s1", &api::SRange::set_s1, py::arg("s1"))
      .def("size", &api::SRange::size)
      .def("WithS", &api::SRange::WithS)
      .def("Intersects", &api::SRange::Intersects, py::arg("s_range"), py::arg("tolerance"))
      .def("GetIntersection", &api::SRange::GetIntersection, py::arg("s_range"), py::arg("tolerance"));

  py::class_<api::LaneSRange>(m, "LaneSRange")
      .def(py::init<const maliput::api::LaneId&, const maliput::api::SRange&>(), py::arg("lane_id"), py::arg("s_range"))
      .def("lane_id", &api::LaneSRange::lane_id, py::return_value_policy::reference_internal)
      .def("s_range", &api::LaneSRange::s_range)
      .def("length", &api::LaneSRange::length)
      .def("Intersects", &api::LaneSRange::Intersects, py::arg("lane_s_range"), py::arg("tolerance"))
      .def("GetIntersection", &api::LaneSRange::GetIntersection, py::arg("lane_s_range"), py::arg("tolerance"));

  py::class_<api::LaneSRoute>(m, "LaneSRoute")
      .def(py::init<>())
      .def(py::init<const std::vector<maliput::api::LaneSRange>&>(), py::arg("ranges"))
      .def("ranges", &api::LaneSRoute::ranges, py::return_value_policy::reference_internal)
      .def("length", &api::LaneSRoute::length)
      .def("Intersects", &api::LaneSRoute::Intersects, py::arg("lane_s_route"), py::arg("tolerance"));

  py::enum_<api::LaneEnd::Which>(m, "Which")
      .value("kStart", api::LaneEnd::Which::kStart)
      .value("kFinish", api::LaneEnd::Which::kFinish)
      .export_values();

  py::class_<api::LaneEnd>(m, "LaneEnd")
      .def(py::init<>())
      .def(py::init<const api::Lane*, api::LaneEnd::Which>(), py::arg("lane"), py::arg("end"),
           // Keep alive, reference: `self` keeps `Lane*` alive.
           py::keep_alive<1, 2>())
      .def_readwrite("lane", &api::LaneEnd::lane)
      .def_readwrite("end", &api::LaneEnd::end);

  py::class_<api::LaneEndSet>(m, "LaneEndSet")
      .def("size", &api::LaneEndSet::size)
      .def("get", &api::LaneEndSet::get, py::arg("index"), py::return_value_policy::reference);

  py::class_<api::BranchPointId>(m, "BranchPointId")
      .def(py::init<std::string>())
      .def(py::detail::hash(py::self))
      .def("string", &api::BranchPointId::string)
      .def("__eq__", &api::BranchPointId::operator==)
      .def("__repr__", [](const api::BranchPointId& id) { return id.string(); });

  py::class_<api::BranchPoint>(m, "BranchPoint")
      .def("id", &api::BranchPoint::id)
      .def("road_geometry", &api::BranchPoint::road_geometry, py::return_value_policy::reference_internal)
      .def("GetConfluentBranches", &api::BranchPoint::GetConfluentBranches, py::arg("end"),
           py::return_value_policy::reference_internal)
      .def("GetOngoingBranches", &api::BranchPoint::GetOngoingBranches, py::arg("end"),
           py::return_value_policy::reference_internal)
      .def("GetDefaultBranch", &api::BranchPoint::GetDefaultBranch, py::arg("end"))
      .def("GetASide", &api::BranchPoint::GetASide, py::return_value_policy::reference_internal)
      .def("GetBSide", &api::BranchPoint::GetBSide, py::return_value_policy::reference_internal);

  py::class_<api::UniqueId>(m, "UniqueId")
      .def(py::init<const std::string&>())
      .def(py::detail::hash(py::self))
      .def("string", &api::UniqueId::string)
      .def("__repr__", &api::UniqueId::string)
      .def("__eq__", &api::UniqueId::operator==)
      .def("__ne__", &api::UniqueId::operator!=);

  auto rules_module = m.def_submodule("rules", "Maliput rules namespace");
  api::bindings::InitializeRulesNamespace(&rules_module);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
  auto intersection_type =
      py::class_<api::Intersection>(m, "Intersection")
          .def("id", &api::Intersection::id, py::return_value_policy::reference_internal)
          .def("Phase", &api::Intersection::Phase)
          .def("SetPhase", &api::Intersection::SetPhase, py::arg("phase_id"), py::arg("next_phase") = std::nullopt,
               py::arg("duration_until") = std::nullopt)
          .def("region", &api::Intersection::region, py::return_value_policy::reference_internal)
          .def("ring_id", &api::Intersection::ring_id, py::return_value_policy::reference_internal)
          .def("bulb_states", &api::Intersection::bulb_states)
          .def("DiscreteValueRuleStates", &api::Intersection::DiscreteValueRuleStates)
          .def("RuleStates", &api::Intersection::RuleStates)
          .def("Includes",
               py::overload_cast<const api::rules::TrafficLight::Id&>(&api::Intersection::Includes, py::const_),
               py::arg("id"))
          .def("Includes",
               py::overload_cast<const api::rules::DiscreteValueRule::Id&>(&api::Intersection::Includes, py::const_),
               py::arg("id"))
          .def("Includes",
               py::overload_cast<const api::rules::RightOfWayRule::Id&>(&api::Intersection::Includes, py::const_),
               py::arg("id"))
          .def("Includes",
               py::overload_cast<const api::InertialPosition&, const api::RoadGeometry*>(&api::Intersection::Includes,
                                                                                         py::const_),
               py::arg("inertial_position"), py::arg("road_geometry"));
#pragma GCC diagnostic pop

  py::class_<api::Intersection::Id>(intersection_type, "Id")
      .def(py::init<std::string>())
      .def(py::detail::hash(py::self))
      .def("string", &api::Intersection::Id::string)
      .def("__eq__", &api::Intersection::Id::operator==)
      .def("__repr__", [](const api::Intersection::Id& id) { return id.string(); });

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
  py::class_<api::IntersectionBook>(m, "IntersectionBook")
      .def("GetIntersections", &api::IntersectionBook::GetIntersections, py::return_value_policy::reference_internal)
      .def("GetIntersection", &api::IntersectionBook::GetIntersection, py::arg("id"),
           py::return_value_policy::reference_internal)
      .def("FindIntersection",
           py::overload_cast<const api::rules::TrafficLight::Id&>(&api::IntersectionBook::FindIntersection),
           py::arg("id"), py::return_value_policy::reference_internal)
      .def("FindIntersection",
           py::overload_cast<const api::rules::DiscreteValueRule::Id&>(&api::IntersectionBook::FindIntersection),
           py::arg("id"), py::return_value_policy::reference_internal)
      .def("FindIntersection",
           py::overload_cast<const api::rules::RightOfWayRule::Id&>(&api::IntersectionBook::FindIntersection),
           py::arg("id"), py::return_value_policy::reference_internal)
      .def("FindIntersection",
           py::overload_cast<const api::InertialPosition&>(&api::IntersectionBook::FindIntersection),
           py::arg("inertial_pos"), py::return_value_policy::reference_internal);
#pragma GCC diagnostic pop
}

}  // namespace bindings
}  // namespace maliput

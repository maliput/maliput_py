#include <maliput/api/junction.h>
#include <maliput/api/lane.h>
#include <maliput/api/lane_data.h>
#include <maliput/api/road_geometry.h>
#include <maliput/api/road_network.h>
#include <maliput/api/segment.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace maliput {
namespace bindings {

namespace py = pybind11;

PYBIND11_MODULE(api, m) {
  // TODO(jadecastro) These bindings are work-in-progress. Expose additional
  // Maliput API features, as necessary (see #7918).

  // TODO(m-chaturvedi) Add doc when typedefs are parsed (#9599)
  py::class_<api::RoadGeometryId>(m, "RoadGeometryId")
      .def(py::init<std::string>())
      .def("string", &api::RoadGeometryId::string, py::return_value_policy::reference_internal);

  py::class_<api::InertialPosition>(m, "InertialPosition")
      .def(py::init<double, double, double>(), py::arg("x"), py::arg("y"), py::arg("z"))
      .def("__eq__", [](const api::InertialPosition& lhs, const api::InertialPosition& rhs) { return lhs == rhs; })
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
      .def_readonly("lane", &api::RoadPosition::lane);

  py::class_<api::RoadPositionResult>(m, "RoadPositionResult")
      .def(py::init<>())
      .def_readwrite("road_position", &api::RoadPositionResult::road_position)
      .def_readwrite("nearest_position", &api::RoadPositionResult::nearest_position)
      .def_readwrite("distance", &api::RoadPositionResult::distance);

  py::class_<api::Rotation>(m, "Rotation")
      .def(py::init<>())
      .def("quat", &api::Rotation::quat, py::return_value_policy::reference_internal)
      .def("rpy", &api::Rotation::rpy);

  py::class_<api::RoadNetwork>(m, "RoadNetwork")
      .def("road_geometry", &api::RoadNetwork::road_geometry, py::return_value_policy::reference_internal);

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
      .def("string", &api::JunctionId::string, py::return_value_policy::reference_internal);

  py::class_<api::Junction>(m, "Junction")
      .def("num_segments", &api::Junction::num_segments)
      .def("segment", &api::Junction::segment, py::return_value_policy::reference_internal)
      .def("id", &api::Junction::id, py::return_value_policy::reference_internal)
      .def("road_geometry", &api::Junction::road_geometry, py::return_value_policy::reference_internal);

  py::class_<api::SegmentId>(m, "SegmentId")
      .def(py::init<std::string>())
      .def("string", &api::SegmentId::string, py::return_value_policy::reference_internal);

  py::class_<api::Segment>(m, "Segment")
      .def("num_lanes", &api::Segment::num_lanes)
      .def("lane", &api::Segment::lane, py::return_value_policy::reference_internal)
      .def("junction", &api::Segment::num_lanes, py::return_value_policy::reference_internal)
      .def("id", &api::Segment::id, py::return_value_policy::reference_internal);

  py::class_<api::LaneId>(m, "LaneId")
      .def(py::init<std::string>())
      .def("string", &api::LaneId::string, py::return_value_policy::reference_internal);

  py::class_<api::Lane>(m, "Lane")
      .def("ToLanePosition", &api::Lane::ToLanePosition)
      .def("ToInertialPosition", &api::Lane::ToInertialPosition)
      .def("GetOrientation", &api::Lane::GetOrientation)
      .def("length", &api::Lane::length)
      .def("id", &api::Lane::id)
      .def("segment", &api::Lane::segment, py::return_value_policy::reference_internal)
      .def("to_left", &api::Lane::to_left, py::return_value_policy::reference_internal)
      .def("to_right", &api::Lane::to_right, py::return_value_policy::reference_internal);
}

}  // namespace bindings
}  // namespace maliput

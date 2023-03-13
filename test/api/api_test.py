#!/usr/bin/env python3

# BSD 3-Clause License
#
# Copyright (c) 2022, Woven Planet. All rights reserved.
# Copyright (c) 2021-2022, Toyota Research Institute. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# * Neither the name of the copyright holder nor the names of its
#   contributors may be used to endorse or promote products derived from
#   this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

"""Unit tests for the maliput::api python binding"""

import math
import unittest

from maliput.api import (
    BranchPoint,
    BranchPointId,
    HBounds,
    InertialPosition,
    Intersection,
    IntersectionBook,
    IsoLaneVelocity,
    Junction,
    JunctionId,
    Lane,
    LaneEnd,
    LaneId,
    LanePosition,
    LanePositionResult,
    LaneSRange,
    LaneSRoute,
    RBounds,
    RoadGeometry,
    RoadGeometryId,
    RoadNetwork,
    RoadPosition,
    RoadPositionResult,
    Rotation,
    Segment,
    SegmentId,
    SRange,
    UniqueId,
    Which,
)

from maliput.math import (
    Vector3,
    Vector4,
)

TOLERANCE = 1e-9


class TestMaliputApi(unittest.TestCase):
    """
    Evaluates the maliput.api bindings for concrete classes or structs.
    """

    def test_road_geometry_id(self):
        """
        Tests the RoadGeometryId binding.
        """
        dut = RoadGeometryId("dut")
        self.assertEqual("dut", dut.string())

    def test_inertial_position(self):
        """
        Tests the InertialPosition binding.
        """
        dut = InertialPosition(x=5., y=10., z=15.)
        self.assertEqual(dut, dut)
        self.assertEqual(Vector3(5., 10., 15.), dut.xyz())
        dut.set_x(dut.x() * 2)
        dut.set_y(dut.y() * 2)
        dut.set_z(dut.z() * 2)
        self.assertEqual(5*2, dut.x())
        self.assertEqual(10*2, dut.y())
        self.assertEqual(15*2, dut.z())
        self.assertEqual(math.sqrt(dut.x()**2 + dut.y()**2 + dut.z()**2), dut.length())
        self.assertEqual(100, dut.Distance(InertialPosition(dut.x() + 100, dut.y(), dut.z())))

    def test_lane_position(self):
        """
        Tests the LanePosition binding.
        """
        dut = LanePosition(s=1., r=2., h=3.)
        self.assertEqual(Vector3(1., 2., 3.), dut.srh())
        dut.set_s(11)
        self.assertEqual(11, dut.s())
        dut.set_r(12)
        self.assertEqual(12, dut.r())
        dut.set_h(13)
        self.assertEqual(13, dut.h())

    def test_lane_position_result(self):
        """
        Tests the LanePositionResult binding.
        """
        dut = LanePositionResult(lane_position=LanePosition(1., 2., 3.),
                                 nearest_position=InertialPosition(4., 5., 6.),
                                 distance=7.)
        self.assertEqual(Vector3(1., 2., 3.), dut.lane_position.srh())
        self.assertEqual(Vector3(4., 5., 6.), dut.nearest_position.xyz())
        self.assertEqual(7., dut.distance)

    def test_empty_lane_position_result(self):
        """
        Tests an empty LanePositionResult binding.
        """
        dut = LanePositionResult()
        self.assertEqual(Vector3(0., 0., 0.), dut.lane_position.srh())
        self.assertEqual(Vector3(0., 0., 0.), dut.nearest_position.xyz())
        self.assertEqual(0., dut.distance)

    def test_empty_road_position(self):
        """
        Tests an empty RoadPosition binding.
        """
        dut = RoadPosition()
        self.assertEqual(None, dut.lane)
        self.assertEqual(Vector3(0., 0., 0.), dut.pos.srh())
        self.assertTrue('ToInertialPosition' in dir(RoadPosition))

    def test_empty_road_position_result(self):
        """
        Tests an empty RoadPositionResult binding.
        """
        dut = RoadPositionResult()
        self.assertEqual(None, dut.road_position.lane)
        self.assertEqual(Vector3(0., 0., 0.), dut.road_position.pos.srh())
        self.assertEqual(InertialPosition(0., 0., 0.), dut.nearest_position)
        self.assertEqual(0, dut.distance)

    def test_identity_rotation(self):
        """
        Tests an empty Rotation binding.
        """
        dut = Rotation()
        self.assertEqual(Vector4(1., 0., 0., 0.), dut.quat().coeffs())
        self.assertAlmostEqual(0., dut.rpy().roll_angle())
        self.assertAlmostEqual(0., dut.rpy().pitch_angle())
        self.assertAlmostEqual(0., dut.rpy().yaw_angle())

    def test_hbounds_default_init(self):
        """
        Tests the HBounds default initializer.
        """
        dut = HBounds()
        self.assertAlmostEqual(0., dut.min_h())
        self.assertAlmostEqual(0., dut.max_h())

    def test_hbounds_custom_init(self):
        """
        Tests the HBounds custom initializer.
        """
        dut = HBounds(-1.2, 3.4)
        self.assertAlmostEqual(-1.2, dut.min_h())
        self.assertAlmostEqual(3.4, dut.max_h())

    def test_hbounds_setter(self):
        """
        Tests the HBounds setters
        """
        dut = HBounds(-1.2, 3.4)
        self.assertAlmostEqual(-1.2, dut.min_h())
        self.assertAlmostEqual(3.4, dut.max_h())

        dut.set_min_h(-2.1)
        self.assertAlmostEqual(-2.1, dut.min_h())

        dut.set_max_h(4.3)
        self.assertAlmostEqual(4.3, dut.max_h())

    def test_rbounds_default_init(self):
        """
        Tests the RBounds default initializer.
        """
        dut = RBounds()
        self.assertAlmostEqual(0., dut.min_r())
        self.assertAlmostEqual(0., dut.max_r())

    def test_rbounds_custom_init(self):
        """
        Tests the RBounds custom initializer.
        """
        dut = RBounds(-1.2, 3.4)
        self.assertAlmostEqual(-1.2, dut.min_r())
        self.assertAlmostEqual(3.4, dut.max_r())

    def test_rbounds_setter(self):
        """
        Tests the RBounds setters
        """
        dut = RBounds(-1.2, 3.4)
        self.assertAlmostEqual(-1.2, dut.min_r())
        self.assertAlmostEqual(3.4, dut.max_r())

        dut.set_min_r(-2.1)
        self.assertAlmostEqual(-2.1, dut.min_r())

        dut.set_max_r(4.3)
        self.assertAlmostEqual(4.3, dut.max_r())

    def test_iso_lane_velocity_default_initializer(self):
        """
        Tests the IsoLaneVelocity default initializer
        """
        dut = IsoLaneVelocity()
        self.assertAlmostEqual(0., dut.sigma_v)
        self.assertAlmostEqual(0., dut.rho_v)
        self.assertAlmostEqual(0., dut.eta_v)

    def test_iso_lane_velocity_custom_initializer(self):
        """
        Tests the IsoLaneVelocity custom initializer
        """
        dut = IsoLaneVelocity(1.2, 3.4, 5.6)
        self.assertAlmostEqual(1.2, dut.sigma_v)
        self.assertAlmostEqual(3.4, dut.rho_v)
        self.assertAlmostEqual(5.6, dut.eta_v)

    def test_iso_lane_velocity_properties(self):
        """
        Tests the IsoLaneVelocity properties
        """
        dut = IsoLaneVelocity(1.2, 3.4, 5.6)

        dut.sigma_v = 0.2
        self.assertAlmostEqual(0.2, dut.sigma_v)

        dut.rho_v = 1.4
        self.assertAlmostEqual(1.4, dut.rho_v)

        dut.eta_v = 2.6
        self.assertAlmostEqual(2.6, dut.eta_v)

    def test_branchpoint_id(self):
        """
        Tests the BranchPointId binding.
        """
        dut = BranchPointId("dut")
        self.assertEqual("dut", dut.string())
        self.assertEqual("dut", dut.__repr__())
        self.assertEqual(BranchPointId("dut"), dut)

    def test_lane_id(self):
        """
        Tests the LaneId binding.
        """
        dut = LaneId("dut")
        self.assertEqual("dut", dut.string())
        self.assertEqual("dut", dut.__repr__())
        self.assertEqual(LaneId("dut"), dut)

    def test_segment_id(self):
        """
        Tests the SegmentId binding.
        """
        dut = SegmentId("dut")
        self.assertEqual("dut", dut.string())
        self.assertEqual("dut", dut.__repr__())
        self.assertEqual(SegmentId("dut"), dut)

    def test_junction_id(self):
        """
        Tests the JunctionId binding.
        """
        dut = JunctionId("dut")
        self.assertEqual("dut", dut.string())
        self.assertEqual("dut", dut.__repr__())
        self.assertEqual(JunctionId("dut"), dut)

    def test_s_range(self):
        """
        Tests the SRange binding.
        """
        dut = SRange(5., 15.)
        self.assertEqual(5., dut.s0())
        self.assertEqual(15., dut.s1())
        self.assertEqual(10, dut.size())
        self.assertEqual(1, dut.WithS())
        # Change SRange
        dut.set_s0(100.)
        dut.set_s1(20.)
        self.assertEqual(100., dut.s0())
        self.assertEqual(20., dut.s1())
        self.assertEqual(0, dut.WithS())
        # Compare with overlapped SRange
        overlapped_s_range = SRange(50., 150.)
        self.assertEqual(True, dut.Intersects(overlapped_s_range, TOLERANCE))
        intersected = dut.GetIntersection(overlapped_s_range, TOLERANCE)
        self.assertFalse(intersected is None)
        self.assertEqual(50., intersected.s0())
        self.assertEqual(100., intersected.s1())
        # Intersects with non-overlapped SRange
        not_overlapped_s_range = SRange(0., 10.)
        intersected = dut.GetIntersection(not_overlapped_s_range, TOLERANCE)
        self.assertTrue(intersected is None)

    def test_lane_s_range(self):
        """
        Tests the LaneSRange binding.
        """
        s_range = SRange(5., 15.)
        lane_id = LaneId("dut_lane")
        dut = LaneSRange(lane_id, s_range)
        print(lane_id)
        print(dut.lane_id())
        self.assertEqual(lane_id, dut.lane_id())
        self.assertEqual(s_range.s0(), dut.s_range().s0())
        self.assertEqual(s_range.s1(), dut.s_range().s1())
        self.assertEqual(s_range.size(), dut.length())
        # Check intersections
        other_lane_s_range = LaneSRange(LaneId("other_lane"), SRange(10., 15.))
        self.assertFalse(dut.Intersects(other_lane_s_range, TOLERANCE))
        overlapped_lane_s_range = LaneSRange(LaneId("dut_lane"), SRange(10., 15.))
        self.assertTrue(dut.Intersects(overlapped_lane_s_range, TOLERANCE))
        not_overlapped_lane_s_range = LaneSRange(LaneId("dut_lane"), SRange(50., 75.))
        self.assertFalse(dut.Intersects(not_overlapped_lane_s_range, TOLERANCE))
        # Check get_intersection methdo
        non_intersected = dut.GetIntersection(other_lane_s_range, TOLERANCE)
        self.assertEqual(non_intersected, None)
        non_intersected = dut.GetIntersection(not_overlapped_lane_s_range, TOLERANCE)
        self.assertEqual(non_intersected, None)
        expected_intersection = LaneSRange(dut.lane_id(), SRange(10., 15.))
        intersected = dut.GetIntersection(overlapped_lane_s_range, TOLERANCE)
        self.assertEqual(intersected.lane_id(), expected_intersection.lane_id())
        self.assertEqual(intersected.s_range().s0(), expected_intersection.s_range().s0())
        self.assertEqual(intersected.s_range().s1(), expected_intersection.s_range().s1())

    def test_lane_s_route(self):
        """
        Tests the LaneSRoute binding.
        """
        dut = LaneSRoute()
        self.assertEqual(0., dut.length())
        self.assertEqual(0., len(dut.ranges()))
        dut = LaneSRoute([
            LaneSRange(LaneId("lane_1"), SRange(20., 100.)),
            LaneSRange(LaneId("lane_2"), SRange(0., 100.)),
            LaneSRange(LaneId("lane_3"), SRange(0., 20.)),
        ])
        self.assertEqual(200., dut.length())
        self.assertEqual(3., len(dut.ranges()))
        # Check intersects
        overlapped_dut = LaneSRoute([
            LaneSRange(LaneId("lane_2"), SRange(50., 75.)),
        ])
        self.assertTrue(dut.Intersects(overlapped_dut, TOLERANCE))
        not_overlapped_dut = LaneSRoute([
            LaneSRange(LaneId("other_lane"), SRange(50., 75.)),
        ])
        self.assertFalse(dut.Intersects(not_overlapped_dut, TOLERANCE))

    def test_lane_end_which(self):
        """
        Tests the LaneEnd::Which binding.
        """
        self.assertFalse(Which.kStart == Which.kFinish)

    def test_lane_end_default_init(self):
        """
        Tests the LaneEnd binding.
        """
        dut = LaneEnd()
        self.assertEqual(None, dut.lane)
        self.assertEqual(Which.kStart, dut.end)

    def test_unique_id(self):
        """
        Tests the UniqueId binding.
        """
        dut = UniqueId("dut")
        self.assertEqual("dut", dut.string())
        self.assertEqual(UniqueId("dut"), dut)
        self.assertNotEqual(dut, UniqueId("another dut"))

    def test_intersection_methods(self):
        """
        Tests that Intersection exposes the right methods.
        """
        dut_type_methods = dir(Intersection)
        self.assertTrue('id' in dut_type_methods)
        self.assertTrue('Phase' in dut_type_methods)
        self.assertTrue('region' in dut_type_methods)
        self.assertTrue('ring_id' in dut_type_methods)
        self.assertTrue('bulb_states' in dut_type_methods)
        self.assertTrue('DiscreteValueRuleStates' in dut_type_methods)
        self.assertTrue('RuleStates' in dut_type_methods)
        self.assertTrue('Includes' in dut_type_methods)

    def test_intersection__id(self):
        """
        Test the Intersection::Id binding.
        """
        dut = Intersection.Id("dut")
        self.assertEqual("dut", dut.string())
        self.assertEqual("dut", dut.__repr__())
        self.assertEqual(Intersection.Id("dut"), dut)

    def test_intersection_book_methods(self):
        """
        Tests that IntersectionBook exposes the right methods.
        """
        dut_type_methods = dir(IntersectionBook)
        self.assertTrue('GetIntersections' in dut_type_methods)
        self.assertTrue('GetIntersection' in dut_type_methods)
        self.assertTrue('FindIntersection' in dut_type_methods)

    def test_road_network_methods(self):
        """
        Tests that RoadNetwork exposes the right methods.
        """
        dut_type_methods = dir(RoadNetwork)
        self.assertTrue('road_geometry' in dut_type_methods)
        self.assertTrue('rulebook' in dut_type_methods)
        self.assertTrue('traffic_light_book' in dut_type_methods)
        self.assertTrue('intersection_book' in dut_type_methods)
        self.assertTrue('phase_ring_book' in dut_type_methods)
        self.assertTrue('right_of_way_rule_state_provider' in dut_type_methods)
        self.assertTrue('phase_provider' in dut_type_methods)
        self.assertTrue('rule_registry' in dut_type_methods)
        self.assertTrue('discrete_value_rule_state_provider' in dut_type_methods)
        self.assertTrue('range_value_rule_state_provider' in dut_type_methods)
        self.assertTrue('Contains' in dut_type_methods)

    def test_lane_methods(self):
        """
        Tests that Lane exposes the right methods.
        """
        dut_type_methods = dir(Lane)
        self.assertTrue('id' in dut_type_methods)
        self.assertTrue('segment' in dut_type_methods)
        self.assertTrue('index' in dut_type_methods)
        self.assertTrue('to_left' in dut_type_methods)
        self.assertTrue('to_right' in dut_type_methods)
        self.assertTrue('length' in dut_type_methods)
        self.assertTrue('lane_bounds' in dut_type_methods)
        self.assertTrue('segment_bounds' in dut_type_methods)
        self.assertTrue('elevation_bounds' in dut_type_methods)
        self.assertTrue('ToInertialPosition' in dut_type_methods)
        self.assertTrue('ToLanePosition' in dut_type_methods)
        self.assertTrue('ToSegmentPosition' in dut_type_methods)
        self.assertTrue('EvalMotionDerivatives' in dut_type_methods)
        self.assertTrue('GetBranchPoint' in dut_type_methods)
        self.assertTrue('GetConfluentBranches' in dut_type_methods)
        self.assertTrue('GetOngoingBranches' in dut_type_methods)
        self.assertTrue('GetDefaultBranch' in dut_type_methods)
        self.assertTrue('Contains' in dut_type_methods)

    def test_segment_methods(self):
        """
        Tests that Segment exposes the right methods.
        """
        dut_type_methods = dir(Segment)
        self.assertTrue('id' in dut_type_methods)
        self.assertTrue('num_lanes' in dut_type_methods)
        self.assertTrue('junction' in dut_type_methods)
        self.assertTrue('lane' in dut_type_methods)

    def test_junction_methods(self):
        """
        Tests that Junction exposes the right methods.
        """
        dut_type_methods = dir(Junction)
        self.assertTrue('id' in dut_type_methods)
        self.assertTrue('num_segments' in dut_type_methods)
        self.assertTrue('segment' in dut_type_methods)
        self.assertTrue('road_geometry' in dut_type_methods)

    def test_brachpoint_methods(self):
        """
        Tests that BranchPoint exposes the right methods.
        """
        dut_type_methods = dir(BranchPoint)
        self.assertTrue('id' in dut_type_methods)
        self.assertTrue('road_geometry' in dut_type_methods)
        self.assertTrue('GetConfluentBranches' in dut_type_methods)
        self.assertTrue('GetOngoingBranches' in dut_type_methods)
        self.assertTrue('GetDefaultBranch' in dut_type_methods)
        self.assertTrue('GetASide' in dut_type_methods)
        self.assertTrue('GetBSide' in dut_type_methods)

    def test_road_geometry_methods(self):
        """
        Tests that RoadGeometry exposes the right methods.
        """
        dut_type_methods = dir(RoadGeometry)
        self.assertTrue('id' in dut_type_methods)
        self.assertTrue('num_junctions' in dut_type_methods)
        self.assertTrue('junction' in dut_type_methods)
        self.assertTrue('ById' in dut_type_methods)
        self.assertTrue('ToRoadPosition' in dut_type_methods)
        self.assertTrue('ToRoadPositionByHint' in dut_type_methods)
        self.assertTrue('FindRoadPositions' in dut_type_methods)

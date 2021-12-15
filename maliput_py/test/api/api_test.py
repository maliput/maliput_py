#!/usr/bin/env python3
#
# Copyright 2021 Toyota Research Institute
#

"""Unit tests for the maliput::api python binding"""

import math
import unittest

from maliput.api import (
    InertialPosition,
    JunctionId,
    LaneEnd,
    LaneId,
    LanePosition,
    LanePositionResult,
    LaneSRange,
    LaneSRoute,
    RoadGeometryId,
    RoadPosition,
    RoadPositionResult,
    Rotation,
    SegmentId,
    SRange,
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

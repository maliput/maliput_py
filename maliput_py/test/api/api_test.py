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
    LaneId,
    LanePosition,
    LanePositionResult,
    RoadGeometryId,
    RoadPosition,
    RoadPositionResult,
    Rotation,
    SegmentId,
)

from maliput.math import (
    Vector3,
    Vector4,
)


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

    def test_segment_id(self):
        """
        Tests the SegmentId binding.
        """
        dut = SegmentId("dut")
        self.assertEqual("dut", dut.string())

    def test_junction_id(self):
        """
        Tests the JunctionId binding.
        """
        dut = JunctionId("dut")
        self.assertEqual("dut", dut.string())

#!/usr/bin/env python3
#
# Copyright 2021 Toyota Research Institute
#

"""Unit tests for the api python binding"""

import unittest

from maliput.api import (
    InertialPosition,
    LaneId,
    LanePosition,
    LanePositionResult,
    RoadGeometryId,
    RoadPosition,
    Rotation,
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
        kDut = RoadGeometryId("dut")
        self.assertEqual("dut", kDut.string())

    def test_inertial_position(self):
        """
        Tests the InertialPosition binding.
        """
        kDut = InertialPosition(x=1., y=2., z=3.)
        self.assertEqual(Vector3(1., 2., 3.), kDut.xyz())

    def test_lane_position(self):
        """
        Tests the LanePosition binding.
        """
        kDut = LanePosition(s=1., r=2., h=3.)
        self.assertEqual(Vector3(1., 2., 3.), kDut.srh())

    def test_lane_position_result(self):
        """
        Tests the LanePositionResult binding.
        """
        kDut = LanePositionResult(lane_position=LanePosition(1., 2., 3.),
                                  nearest_position=InertialPosition(4., 5., 6.),
                                  distance=7.)
        self.assertEqual(Vector3(1., 2., 3.), kDut.lane_position.srh())
        self.assertEqual(Vector3(4., 5., 6.), kDut.nearest_position.xyz())
        self.assertEqual(7., kDut.distance)

    def test_empty_lane_position_result(self):
        """
        Tests an empty LanePositionResult binding.
        """
        kDut = LanePositionResult()
        self.assertEqual(Vector3(0., 0., 0.), kDut.lane_position.srh())
        self.assertEqual(Vector3(0., 0., 0.), kDut.nearest_position.xyz())
        self.assertEqual(0., kDut.distance)

    def test_empty_road_position(self):
        """
        Tests an empty RoadPosition binding.
        """
        kDut = RoadPosition()
        self.assertEqual(None, kDut.lane)
        self.assertEqual(Vector3(0., 0., 0.), kDut.pos.srh())

    def test_identity_rotation(self):
        """
        Tests an Rotation binding.
        """
        kDut = Rotation()
        self.assertEqual(Vector4(1., 0., 0., 0.), kDut.quat().coeffs())
        self.assertAlmostEqual(0., kDut.rpy().roll_angle())
        self.assertAlmostEqual(0., kDut.rpy().pitch_angle())
        self.assertAlmostEqual(0., kDut.rpy().yaw_angle())

    def test_lane_id(self):
        """
        """
        kDut = LaneId("dut")
        self.assertEqual("dut", kDut.string())

#!/usr/bin/env python3

# BSD 3-Clause License
#
# Copyright (c) 2026, Woven by Toyota
# All rights reserved.
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

"""Unit tests for the from_capsule() interop API of the maliput::api bindings.

The C++ objects are owned by the `interop_test_helper` extension module, which
hands out PyCapsules the way an external consumer (e.g. Rust/PyO3 bindings)
would. See interop_test_helper.cc.
"""

import gc
import unittest

from maliput.api import (
    RoadGeometry,
    RoadNetwork,
)

from interop_test_helper import (
    RoadNetworkOwner,
)


class TestRoadNetworkFromCapsule(unittest.TestCase):
    """
    Evaluates RoadNetwork.from_capsule().
    """

    def test_round_trip(self):
        """
        Tests that a capsule holding a C++-owned RoadNetwork* is wrapped as a
        usable Python RoadNetwork.
        """
        owner = RoadNetworkOwner()
        dut = RoadNetwork.from_capsule(owner.road_network_capsule(), owner)
        self.assertIsInstance(dut, RoadNetwork)
        # The wrapped object must reach the same underlying RoadGeometry.
        self.assertEqual(dut.road_geometry().id().string(), owner.road_geometry_id())
        self.assertEqual(dut.road_geometry().num_junctions(), owner.num_junctions())

    def test_wrong_capsule_name(self):
        """
        Tests that a capsule whose name does not match is rejected.
        """
        owner = RoadNetworkOwner()
        with self.assertRaises(ValueError):
            RoadNetwork.from_capsule(owner.misnamed_capsule(), owner)

    def test_unnamed_capsule(self):
        """
        Tests that a capsule with no name at all is rejected.
        """
        owner = RoadNetworkOwner()
        with self.assertRaises(ValueError):
            RoadNetwork.from_capsule(owner.unnamed_capsule(), owner)

    def test_cross_wired_capsule(self):
        """
        Tests that a RoadGeometry capsule does not satisfy RoadNetwork.
        """
        owner = RoadNetworkOwner()
        with self.assertRaises(ValueError):
            RoadNetwork.from_capsule(owner.road_geometry_capsule(), owner)


class TestRoadGeometryFromCapsule(unittest.TestCase):
    """
    Evaluates RoadGeometry.from_capsule().
    """

    def test_round_trip(self):
        """
        Tests that a capsule holding a C++-owned RoadGeometry* is wrapped as a
        usable Python RoadGeometry.
        """
        owner = RoadNetworkOwner()
        dut = RoadGeometry.from_capsule(owner.road_geometry_capsule(), owner)
        self.assertIsInstance(dut, RoadGeometry)
        self.assertEqual(dut.id().string(), owner.road_geometry_id())
        self.assertEqual(dut.num_junctions(), owner.num_junctions())
        self.assertEqual(dut.num_branch_points(), owner.num_branch_points())

    def test_matches_road_network_accessor(self):
        """
        Tests that the capsule route and the RoadNetwork.road_geometry()
        accessor yield the same underlying object.
        """
        owner = RoadNetworkOwner()
        road_network = RoadNetwork.from_capsule(owner.road_network_capsule(), owner)
        dut = RoadGeometry.from_capsule(owner.road_geometry_capsule(), owner)
        self.assertEqual(dut.id().string(), road_network.road_geometry().id().string())
        self.assertEqual(dut.num_junctions(), road_network.road_geometry().num_junctions())

    def test_wrong_capsule_name(self):
        """
        Tests that a capsule whose name does not match is rejected.
        """
        owner = RoadNetworkOwner()
        with self.assertRaises(ValueError):
            RoadGeometry.from_capsule(owner.misnamed_capsule(), owner)

    def test_cross_wired_capsule(self):
        """
        Tests that a RoadNetwork capsule does not satisfy RoadGeometry.
        """
        owner = RoadNetworkOwner()
        with self.assertRaises(ValueError):
            RoadGeometry.from_capsule(owner.road_network_capsule(), owner)


class TestOwnerLifetime(unittest.TestCase):
    """
    Evaluates that from_capsule() ties the returned object's lifetime to
    `owner`, which is what keeps the underlying C++ memory alive.
    """

    def test_owner_kept_alive(self):
        """
        Tests that dropping the last external reference to `owner` does not
        destroy it while the wrapped object is still in use.
        """
        owner = RoadNetworkOwner()
        expected_id = owner.road_geometry_id()
        dut = RoadGeometry.from_capsule(owner.road_geometry_capsule(), owner)
        del owner
        gc.collect()
        # If the keep-alive were missing, the owner (and its RoadNetwork) would
        # already be freed and this would read released memory.
        self.assertEqual(dut.id().string(), expected_id)

    def test_owner_survives_via_road_network(self):
        """
        Tests the same keep-alive behavior through RoadNetwork.
        """
        owner = RoadNetworkOwner()
        expected_junctions = owner.num_junctions()
        dut = RoadNetwork.from_capsule(owner.road_network_capsule(), owner)
        del owner
        gc.collect()
        self.assertEqual(dut.road_geometry().num_junctions(), expected_junctions)


if __name__ == '__main__':
    unittest.main()

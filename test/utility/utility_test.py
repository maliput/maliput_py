#!/usr/bin/env python3

# BSD 3-Clause License
#
# Copyright (c) 2023, Woven Planet. All rights reserved.
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

"""Unit tests for the maliput::utility python binding"""

import unittest


from maliput.api import (
    InertialPosition,
)


from maliput.utility import (
    GenerateObjFile,
    ObjFeatures
)


TOLERANCE = 1e-9


class TestMaliputUtility(unittest.TestCase):
    """
    Evaluates the maliput.utility bindings for concrete classes or structs.
    """

    def test_generate_obj_file_method(self):
        """
        Tests that GenerateObjFile method exists.
        """
        dut_name = GenerateObjFile.__name__
        self.assertEqual('GenerateObjFile', dut_name)

    def test_obj_features(self):
        """
        Tests the ObjFeatures binding.
        """
        dut = ObjFeatures()

        self.assertEqual(1.0, dut.max_grid_unit)
        self.assertEqual(5.0, dut.min_grid_resolution)
        self.assertEqual(True, dut.draw_stripes)
        self.assertEqual(True, dut.draw_arrows)
        self.assertEqual(True, dut.draw_lane_haze)
        self.assertEqual(True, dut.draw_branch_points)
        self.assertEqual(True, dut.draw_elevation_bounds)
        self.assertEqual(False, dut.off_grid_mesh_generation)
        self.assertEqual(0.0, dut.simplify_mesh_threshold)
        self.assertEqual(0.25, dut.stripe_width)
        self.assertEqual(0.05, dut.stripe_elevation)
        self.assertEqual(0.05, dut.arrow_elevation)
        self.assertEqual(0.02, dut.lane_haze_elevation)
        self.assertEqual(0.5, dut.branch_point_elevation)
        self.assertEqual(0.5, dut.branch_point_height)
        self.assertEqual(InertialPosition(0., 0., 0.), dut.origin)
        self.assertEqual([], dut.highlighted_segments)

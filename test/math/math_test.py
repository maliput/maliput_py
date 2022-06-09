#!/usr/bin/env python3

# BSD 3-Clause License
#
# Copyright (c) 2022, Woven Planet. All rights reserved.
# Copyright (c) 2020-2022, Toyota Research Institute. All rights reserved.
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

"""Unit tests for the maliput::math python binding"""

import math as m
import unittest

from maliput.math import (
    Quaternion,
    RollPitchYaw,
    Vector3,
    Vector4,
)


class TestMaliputMath(unittest.TestCase):
    """
    Unit tests for the math python binding
    """
    def test_vector3(self):
        """
        Evaluates the constructor and accessors.
        """
        kDut = Vector3(25., 158., 33.)
        self.assertTrue(kDut.size() == 3)
        self.assertTrue(kDut.x() == 25.)
        self.assertTrue(kDut.y() == 158.)
        self.assertTrue(kDut.z() == 33.)
        self.assertTrue(kDut[0] == 25.)
        self.assertTrue(kDut[1] == 158.)
        self.assertTrue(kDut[2] == 33.)
        self.assertTrue(kDut == Vector3(25., 158., 33.))
        self.assertTrue(kDut != Vector3(33., 158., 25.))
        self.assertEqual(kDut.__str__(), "{25, 158, 33}")

    def test_vector4(self):
        """
        Evaluates the constructor and accessors.
        """
        kDut = Vector4(25., 158., 33., 0.02)
        self.assertTrue(kDut.size() == 4)
        self.assertTrue(kDut.x() == 25.)
        self.assertTrue(kDut.y() == 158.)
        self.assertTrue(kDut.z() == 33.)
        self.assertTrue(kDut.w() == 0.02)
        self.assertTrue(kDut[0] == 25.)
        self.assertTrue(kDut[1] == 158.)
        self.assertTrue(kDut[2] == 33.)
        self.assertTrue(kDut[3] == 0.02)
        self.assertTrue(kDut == Vector4(25., 158., 33., 0.02))
        self.assertTrue(kDut != Vector4(0.02, 33., 158., 25.))
        self.assertEqual(kDut.__str__(), "{25, 158, 33, 0.02}")

    def test_rollpitchyaw(self):
        """
        Evaluates the constructor and accessors.
        """
        kDut = RollPitchYaw(m.pi/2, 0., m.pi/2)
        self.assertTrue(kDut.roll_angle() == m.pi/2)
        self.assertTrue(kDut.pitch_angle() == 0.)
        self.assertTrue(kDut.yaw_angle() == m.pi/2)
        quat = kDut.ToQuaternion()
        kExpectedQuat = Quaternion(0.5, 0.5, 0.5, 0.5)
        self.assertAlmostEqual(quat.w(), kExpectedQuat.w())
        self.assertAlmostEqual(quat.x(), kExpectedQuat.x())
        self.assertAlmostEqual(quat.y(), kExpectedQuat.y())
        self.assertAlmostEqual(quat.z(), kExpectedQuat.z())
        self.assertEqual(RollPitchYaw(1.5, 0.5, -1.5).__str__(), "{1.5, 0.5, -1.5}")

    def test_quaternion(self):
        """
        Evaluates the constructor and accessors.
        """
        kDut = Quaternion(0.884, 0.306, 0.177, 0.306)
        self.assertTrue(kDut.w() == 0.884)
        self.assertTrue(kDut.x() == 0.306)
        self.assertTrue(kDut.y() == 0.177)
        self.assertTrue(kDut.z() == 0.306)
        self.assertTrue(kDut.coeffs() == Vector4(0.884, 0.306, 0.177, 0.306))
        self.assertEqual(kDut.__str__(), "(w: 0.884, x: 0.306, y: 0.177, z: 0.306)")

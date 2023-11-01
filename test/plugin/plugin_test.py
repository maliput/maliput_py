#!/usr/bin/env python3

# BSD 3-Clause License
#
# Copyright (c) 2023, Woven by Toyota
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

"""Unit tests for the maliput::plugin python binding"""

import unittest

from maliput.plugin import (
    MaliputPlugin,
    MaliputPluginManager,
    MaliputPluginType,
)


class TestMaliputPlugin(unittest.TestCase):
    """
    Evaluates the maliput.plugin bindings for concrete classes or structs.
    """

    def test_plugin_entities(self):
        """
        Tests the maliput.plugin module entities.
        """
        import maliput.plugin
        dut_type_entities = dir(maliput.plugin)
        self.assertTrue('MaliputPluginType' in dut_type_entities)
        self.assertTrue('MaliputPluginManager' in dut_type_entities)
        self.assertTrue('MaliputPlugin' in dut_type_entities)
        self.assertTrue('create_road_network' in dut_type_entities)

    def test_maliput_plugin_id(self):
        """
        Tests the MaliputPlugin::Id class methods.
        """
        dut = MaliputPlugin.Id('test_id')
        self.assertEqual(dut.string(), 'test_id')
        self.assertEqual(dut, dut)
        self.assertNotEqual(dut, MaliputPlugin.Id('test_id2'))

    def test_maliput_plugin_methods(self):
        """
        Tests the MaliputPlugin class methods.
        """
        dut_type_methods = dir(MaliputPlugin)
        self.assertTrue('GetId' in dut_type_methods)
        self.assertTrue('GetType' in dut_type_methods)

    def test_maliput_plugin_manager_methods(self):
        """
        Tests the MaliputPluginManager class methods.
        """
        dut_type_methods = dir(MaliputPluginManager)
        self.assertTrue('GetPlugin' in dut_type_methods)
        self.assertTrue('AddPlugin' in dut_type_methods)
        self.assertTrue('ListPlugins' in dut_type_methods)

    def test_maliput_plugin_type(self):
        """
        Tests the MaliputPluginType enum.
        """
        self.assertEqual(MaliputPluginType.kRoadNetworkLoader, MaliputPluginType.kRoadNetworkLoader)

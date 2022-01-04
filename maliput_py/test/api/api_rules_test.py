#!/usr/bin/env python3
#
# Copyright 2021 Toyota Research Institute
#

"""Unit tests for the maliput::api::rules python binding"""

import unittest

from maliput.api import (
    LaneId,
    LaneSRange,
    LaneSRoute,
    SRange,
    UniqueId,
)
from maliput.api.rules import (
    DiscreteValueRule,
    RangeValueRule,
    Rule,
    RuleRegistry,
)


class TestMaliputApiRules(unittest.TestCase):
    """
    Evaluates the maliput.api.rules bindings for concrete classes or structs.
    """

    def test_rule_id(self):
        """
        Tests the Rule::Id binding.
        """
        dut = Rule.Id("dut")
        self.assertEqual("dut", dut.string())
        self.assertEqual(Rule.Id("dut"), dut)

    def test_rule_type_id(self):
        """
        Tests the Rule::TypeId binding.
        """
        dut = Rule.TypeId("dut")
        self.assertEqual("dut", dut.string())
        self.assertEqual(Rule.TypeId("dut"), dut)

    def test_rule_state_default_constructor(self):
        """
        Tests the Rule::State default constructor.
        """
        dut = Rule.State()
        self.assertEqual(Rule.State.kStrict, dut.severity)
        self.assertEqual({}, dut.related_rules)
        self.assertEqual({}, dut.related_unique_ids)

    def test_rule_state_non_default_constructor(self):
        """
        Tests the Rule::State non-default constructor binding.
        """
        severity = Rule.State.kBestEffort
        related_rules = {"type_I": [Rule.Id("id_a"), Rule.Id("id_b")],
                         "type_II": [Rule.Id("id_c")]}
        related_unique_ids = {"type_III": [UniqueId("uid_a"), UniqueId("uid_b")],
                              "type_IV": [UniqueId("id_c")]}
        dut = Rule.State(severity, related_rules, related_unique_ids)
        self.assertEqual(severity, dut.severity)
        self.assertEqual(related_rules, dut.related_rules)
        self.assertEqual(related_unique_ids, dut.related_unique_ids)
        self.assertEqual(Rule.State(severity, related_rules, related_unique_ids), dut)
        self.assertNotEqual(Rule.State(), dut)

    def test_rule(self):
        """
        Tests the Rule binding.
        """
        rule_id = Rule.Id("id")
        type_id = Rule.TypeId("type_id")
        zone = LaneSRoute([LaneSRange(LaneId("lane_1"), SRange(0., 100.))])
        dut = Rule(rule_id, type_id, zone)
        self.assertEqual(rule_id, dut.id())
        self.assertEqual(type_id, dut.type_id())
        self.assertEqual(1, len(dut.zone().ranges()))
        self.assertEqual(LaneId("lane_1"), dut.zone().ranges()[0].lane_id())
        self.assertEqual(0., dut.zone().ranges()[0].s_range().s0())
        self.assertEqual(100., dut.zone().ranges()[0].s_range().s1())
        self.assertAlmostEqual(100., dut.zone().length(), 1e-9)

    def test_discrete_value_default_constructor(self):
        """
        Tests the DiscreteValueRule::DiscreteValue default constructor binding.
        """
        dut = DiscreteValueRule.DiscreteValue()
        self.assertEqual(Rule.State.kStrict, dut.severity)
        self.assertEqual({}, dut.related_rules)
        self.assertEqual({}, dut.related_unique_ids)
        self.assertEqual("", dut.value)

    def test_discrete_value_non_default_constructor(self):
        """
        Tests the DiscreteValueRule::DiscreteValue non-default constructor binding.
        """
        severity = Rule.State.kBestEffort
        related_rules = {"type_I": [Rule.Id("id_a"), Rule.Id("id_b")],
                         "type_II": [Rule.Id("id_c")]}
        related_unique_ids = {"type_III": [UniqueId("uid_a"), UniqueId("uid_b")],
                              "type_IV": [UniqueId("id_c")]}
        value = "a value"
        dut = DiscreteValueRule.DiscreteValue(severity, related_rules, related_unique_ids, value)
        self.assertEqual(severity, dut.severity)
        self.assertEqual(related_rules, dut.related_rules)
        self.assertEqual(related_unique_ids, dut.related_unique_ids)
        self.assertEqual(value, dut.value)
        self.assertEqual(DiscreteValueRule.DiscreteValue(severity, related_rules,
                                                         related_unique_ids, value),
                         dut)
        self.assertNotEqual(DiscreteValueRule.DiscreteValue(severity, related_rules,
                                                            related_unique_ids, "another value"),
                            dut)

    def test_discrete_value_rule(self):
        """
        Tests the DiscreteValueRule binding.
        """
        severity = Rule.State.kBestEffort
        related_rules = {"type_I": [Rule.Id("id_a"), Rule.Id("id_b")],
                         "type_II": [Rule.Id("id_c")]}
        related_unique_ids = {"type_III": [UniqueId("uid_a"), UniqueId("uid_b")],
                              "type_IV": [UniqueId("id_c")]}
        value = "a value"
        discrete_value = DiscreteValueRule.DiscreteValue(severity, related_rules,
                                                         related_unique_ids, value)

        rule_id = Rule.Id("id")
        type_id = Rule.TypeId("type_id")
        zone = LaneSRoute([LaneSRange(LaneId("lane_1"), SRange(0., 100.))])
        dut = DiscreteValueRule(rule_id, type_id, zone, [discrete_value])

        self.assertEqual(rule_id, dut.id())
        self.assertEqual(type_id, dut.type_id())
        self.assertEqual(1, len(dut.zone().ranges()))
        self.assertEqual(LaneId("lane_1"), dut.zone().ranges()[0].lane_id())
        self.assertEqual(0., dut.zone().ranges()[0].s_range().s0())
        self.assertEqual(100., dut.zone().ranges()[0].s_range().s1())
        self.assertAlmostEqual(100., dut.zone().length(), 1e-9)
        self.assertEqual([discrete_value], dut.values())

    def test_range_default_constructor(self):
        """
        Tests the RangeValueRule::Range default constructor binding.
        """
        dut = RangeValueRule.Range()
        self.assertEqual(Rule.State.kStrict, dut.severity)
        self.assertEqual({}, dut.related_rules)
        self.assertEqual({}, dut.related_unique_ids)
        self.assertEqual("", dut.description)
        self.assertEqual(0., dut.min)
        self.assertEqual(0., dut.max)

    def test_range_non_default_constructor(self):
        """
        Tests the RangeValueRule::Range non-default constructor binding.
        """
        severity = Rule.State.kBestEffort
        related_rules = {"type_I": [Rule.Id("id_a"), Rule.Id("id_b")],
                         "type_II": [Rule.Id("id_c")]}
        related_unique_ids = {"type_III": [UniqueId("uid_a"), UniqueId("uid_b")],
                              "type_IV": [UniqueId("id_c")]}
        description = "a description"
        min_value = 12.34
        max_value = 56.78
        dut = RangeValueRule.Range(severity, related_rules, related_unique_ids, description,
                                   min_value, max_value)
        self.assertEqual(severity, dut.severity)
        self.assertEqual(related_rules, dut.related_rules)
        self.assertEqual(related_unique_ids, dut.related_unique_ids)
        self.assertEqual(description, dut.description)
        self.assertEqual(min_value, dut.min)
        self.assertEqual(max_value, dut.max)
        self.assertEqual(RangeValueRule.Range(severity, related_rules, related_unique_ids,
                                              description, min_value, max_value),
                         dut)
        self.assertNotEqual(RangeValueRule.Range(severity, related_rules, related_unique_ids,
                                                 "another description", min_value, max_value),
                            dut)
        self.assertFalse(dut < RangeValueRule.Range(severity, related_rules, related_unique_ids,
                                                    description, 0., max_value))
        self.assertTrue(dut < RangeValueRule.Range(severity, related_rules, related_unique_ids,
                                                   description, max_value, 2. * max_value))

    def test_range_value_rule(self):
        """
        Tests the RangeValueRule binding.
        """
        severity = Rule.State.kBestEffort
        related_rules = {"type_I": [Rule.Id("id_a"), Rule.Id("id_b")],
                         "type_II": [Rule.Id("id_c")]}
        related_unique_ids = {"type_III": [UniqueId("uid_a"), UniqueId("uid_b")],
                              "type_IV": [UniqueId("id_c")]}
        description = "a value"
        min_value = 12.34
        max_value = 56.78
        range_value = RangeValueRule.Range(severity, related_rules, related_unique_ids, description,
                                           min_value, max_value)

        rule_id = Rule.Id("id")
        type_id = Rule.TypeId("type_id")
        zone = LaneSRoute([LaneSRange(LaneId("lane_1"), SRange(0., 100.))])
        dut = RangeValueRule(rule_id, type_id, zone, [range_value])

        self.assertEqual(rule_id, dut.id())
        self.assertEqual(type_id, dut.type_id())
        self.assertEqual(1, len(dut.zone().ranges()))
        self.assertEqual(LaneId("lane_1"), dut.zone().ranges()[0].lane_id())
        self.assertEqual(0., dut.zone().ranges()[0].s_range().s0())
        self.assertEqual(100., dut.zone().ranges()[0].s_range().s1())
        self.assertAlmostEqual(100., dut.zone().length(), 1e-9)
        self.assertEqual([range_value], dut.ranges())

    def test_empty_rule_registry(self):
        """
        Tests the RuleRegistry constructor and empty registry bindings.
        """
        dut = RuleRegistry()
        self.assertEqual({}, dut.RangeValueRuleTypes())
        self.assertEqual({}, dut.DiscreteValueRuleTypes())

    def test_rule_registry_register_and_retrieve_ranges(self):
        """
        Tests the RuleRegistry::RegisterRangeValueRule and
        RuleRegistry::GetPossibleStatesOfRuleType bindings.
        """
        range_type_id_a = Rule.TypeId("range_type_id_a")
        range_a = RangeValueRule.Range(
            Rule.State.kBestEffort, {"rule_type_I": [Rule.Id("id_a")]},
            {"type_II": [UniqueId("uid_a"), UniqueId("uid_b")]}, "a description", 12.34, 56.78)

        range_type_id_b = Rule.TypeId("range_type_id_b")
        range_b = RangeValueRule.Range(
            Rule.State.kStrict, {"rule_type_II": [Rule.Id("id_b")]},
            {"type_III": [UniqueId("uid_c"), UniqueId("uid_d")]}, "a description", 12.34, 56.78)

        dut = RuleRegistry()
        dut.RegisterRangeValueRule(range_type_id_a, [range_a])
        dut.RegisterRangeValueRule(range_type_id_b, [range_b])

        self.assertEqual({range_type_id_a: [range_a], range_type_id_b: [range_b]},
                         dut.RangeValueRuleTypes())

        result = dut.GetPossibleStatesOfRuleType(range_type_id_a)
        self.assertTrue(result is not None)
        self.assertEqual(range_type_id_a, result.type_id)
        self.assertEqual([range_a], result.rule_values)

        result = dut.GetPossibleStatesOfRuleType(range_type_id_b)
        self.assertTrue(result is not None)
        self.assertEqual(range_type_id_b, result.type_id)
        self.assertEqual([range_b], result.rule_values)

        result = dut.GetPossibleStatesOfRuleType(Rule.TypeId("does not exist"))
        self.assertTrue(result is None)

    def test_rule_registry_register_and_retrieve_discrete_values(self):
        """
        Tests the RuleRegistry::RegisterDiscreteValueRule and
        RuleRegistry::GetPossibleStatesOfRuleType bindings.
        """
        discrete_value_type_id_a = Rule.TypeId("discrete_value_type_id_a")
        discrete_value_a = DiscreteValueRule.DiscreteValue(
            Rule.State.kBestEffort, {"rule_type_I": [Rule.Id("id_a")]},
            {"type_II": [UniqueId("uid_a"), UniqueId("uid_b")]}, "value 1")

        discrete_value_type_id_b = Rule.TypeId("discrete_value_type_id_b")
        discrete_value_b = DiscreteValueRule.DiscreteValue(
            Rule.State.kStrict, {"rule_type_II": [Rule.Id("id_a")]},
            {"type_III": [UniqueId("uid_c"), UniqueId("uid_d")]}, "value 2")

        dut = RuleRegistry()
        dut.RegisterDiscreteValueRule(discrete_value_type_id_a, [discrete_value_a])
        dut.RegisterDiscreteValueRule(discrete_value_type_id_b,
                                      [discrete_value_a, discrete_value_b])

        self.assertEqual({discrete_value_type_id_a: [discrete_value_a],
                          discrete_value_type_id_b: [discrete_value_a, discrete_value_b]},
                         dut.DiscreteValueRuleTypes())

        result = dut.GetPossibleStatesOfRuleType(discrete_value_type_id_a)
        self.assertTrue(result is not None)
        self.assertEqual(discrete_value_type_id_a, result.type_id)
        self.assertEqual([discrete_value_a], result.rule_values)

        result = dut.GetPossibleStatesOfRuleType(discrete_value_type_id_b)
        self.assertTrue(result is not None)
        self.assertEqual(discrete_value_type_id_b, result.type_id)
        self.assertEqual([discrete_value_a, discrete_value_b], result.rule_values)

        result = dut.GetPossibleStatesOfRuleType(Rule.TypeId("does not exist"))
        self.assertTrue(result is None)

    def test_rule_registry_build_range_value_rule(self):
        """
        Tests the RuleRegistry::BuildRangeValueRule binding.
        """
        range_type_id = Rule.TypeId("range_type_id")
        range_a = RangeValueRule.Range(
            Rule.State.kBestEffort, {"rule_type_I": [Rule.Id("id_a")]},
            {"type_II": [UniqueId("uid_a"), UniqueId("uid_b")]}, "a description", 12.34, 56.78)
        range_b = RangeValueRule.Range(
            Rule.State.kStrict, {"rule_type_II": [Rule.Id("id_b")]},
            {"type_III": [UniqueId("uid_c"), UniqueId("uid_d")]}, "a description", 12.34, 56.78)

        dut = RuleRegistry()
        dut.RegisterRangeValueRule(range_type_id, [range_a, range_b])

        rule_id = Rule.Id("rule_id")
        zone = LaneSRoute([LaneSRange(LaneId("lane_1"), SRange(0., 100.))])

        rule_a = dut.BuildRangeValueRule(rule_id, range_type_id, zone, [range_a])
        self.assertEqual(rule_id, rule_a.id())
        self.assertEqual(range_type_id, rule_a.type_id())
        self.assertEqual(1, len(rule_a.zone().ranges()))
        self.assertEqual(LaneId("lane_1"), rule_a.zone().ranges()[0].lane_id())
        self.assertEqual(0., rule_a.zone().ranges()[0].s_range().s0())
        self.assertEqual(100., rule_a.zone().ranges()[0].s_range().s1())
        self.assertAlmostEqual(100., rule_a.zone().length(), 1e-9)
        self.assertEqual([range_a], rule_a.ranges())

        rule_b = dut.BuildRangeValueRule(rule_id, range_type_id, zone, [range_b])
        self.assertEqual(rule_id, rule_b.id())
        self.assertEqual(range_type_id, rule_b.type_id())
        self.assertEqual(1, len(rule_b.zone().ranges()))
        self.assertEqual(LaneId("lane_1"), rule_b.zone().ranges()[0].lane_id())
        self.assertEqual(0., rule_b.zone().ranges()[0].s_range().s0())
        self.assertEqual(100., rule_b.zone().ranges()[0].s_range().s1())
        self.assertAlmostEqual(100., rule_b.zone().length(), 1e-9)
        self.assertEqual([range_b], rule_b.ranges())

        rule_ab = dut.BuildRangeValueRule(rule_id, range_type_id, zone, [range_a, range_b])
        self.assertEqual(rule_id, rule_ab.id())
        self.assertEqual(range_type_id, rule_ab.type_id())
        self.assertEqual(1, len(rule_ab.zone().ranges()))
        self.assertEqual(LaneId("lane_1"), rule_ab.zone().ranges()[0].lane_id())
        self.assertEqual(0., rule_ab.zone().ranges()[0].s_range().s0())
        self.assertEqual(100., rule_ab.zone().ranges()[0].s_range().s1())
        self.assertAlmostEqual(100., rule_ab.zone().length(), 1e-9)
        self.assertEqual([range_a, range_b], rule_ab.ranges())

    def test_rule_registry_build_discrete_value_rule(self):
        """
        Tests the RuleRegistry::BuildDiscreteValueRule binding.
        """
        discrete_value_type_id = Rule.TypeId("discrete_value_type_id")
        discrete_value_a = DiscreteValueRule.DiscreteValue(
            Rule.State.kBestEffort, {"rule_type_I": [Rule.Id("id_a")]},
            {"type_II": [UniqueId("uid_a"), UniqueId("uid_b")]}, "value 1")
        discrete_value_b = DiscreteValueRule.DiscreteValue(
            Rule.State.kStrict, {"rule_type_II": [Rule.Id("id_a")]},
            {"type_III": [UniqueId("uid_c"), UniqueId("uid_d")]}, "value 2")

        dut = RuleRegistry()
        dut.RegisterDiscreteValueRule(discrete_value_type_id, [discrete_value_a, discrete_value_b])

        rule_id = Rule.Id("rule_id")
        zone = LaneSRoute([LaneSRange(LaneId("lane_1"), SRange(0., 100.))])

        rule_a = dut.BuildDiscreteValueRule(rule_id, discrete_value_type_id, zone,
                                            [discrete_value_a])
        self.assertEqual(rule_id, rule_a.id())
        self.assertEqual(discrete_value_type_id, rule_a.type_id())
        self.assertEqual(1, len(rule_a.zone().ranges()))
        self.assertEqual(LaneId("lane_1"), rule_a.zone().ranges()[0].lane_id())
        self.assertEqual(0., rule_a.zone().ranges()[0].s_range().s0())
        self.assertEqual(100., rule_a.zone().ranges()[0].s_range().s1())
        self.assertAlmostEqual(100., rule_a.zone().length(), 1e-9)
        self.assertEqual([discrete_value_a], rule_a.values())

        rule_b = dut.BuildDiscreteValueRule(rule_id, discrete_value_type_id, zone,
                                            [discrete_value_b])
        self.assertEqual(rule_id, rule_b.id())
        self.assertEqual(discrete_value_type_id, rule_b.type_id())
        self.assertEqual(1, len(rule_b.zone().ranges()))
        self.assertEqual(LaneId("lane_1"), rule_b.zone().ranges()[0].lane_id())
        self.assertEqual(0., rule_b.zone().ranges()[0].s_range().s0())
        self.assertEqual(100., rule_b.zone().ranges()[0].s_range().s1())
        self.assertAlmostEqual(100., rule_b.zone().length(), 1e-9)
        self.assertEqual([discrete_value_b], rule_b.values())

        rule_ab = dut.BuildDiscreteValueRule(rule_id, discrete_value_type_id, zone,
                                             [discrete_value_a, discrete_value_b])
        self.assertEqual(rule_id, rule_ab.id())
        self.assertEqual(discrete_value_type_id, rule_ab.type_id())
        self.assertEqual(1, len(rule_ab.zone().ranges()))
        self.assertEqual(LaneId("lane_1"), rule_ab.zone().ranges()[0].lane_id())
        self.assertEqual(0., rule_ab.zone().ranges()[0].s_range().s0())
        self.assertEqual(100., rule_ab.zone().ranges()[0].s_range().s1())
        self.assertAlmostEqual(100., rule_ab.zone().length(), 1e-9)
        self.assertEqual([discrete_value_a, discrete_value_b], rule_ab.values())

// BSD 3-Clause License
//
// Copyright (c) 2022, Woven Planet. All rights reserved.
// Copyright (c) 2020-2022, Toyota Research Institute. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include "bindings/api_rules_py.h"

#include <maliput/api/rules/discrete_value_rule.h>
#include <maliput/api/rules/discrete_value_rule_state_provider.h>
// TODO: Should be removed as DirectionUsageRule gets deprecated.
#include <maliput/api/rules/direction_usage_rule.h>
#include <maliput/api/rules/phase.h>
#include <maliput/api/rules/phase_provider.h>
#include <maliput/api/rules/phase_ring.h>
#include <maliput/api/rules/phase_ring_book.h>
#include <maliput/api/rules/range_value_rule.h>
#include <maliput/api/rules/range_value_rule_state_provider.h>
#include <maliput/api/rules/rule.h>
// TODO: Should be removed as RightOfWayRule gets deprecated.
#include <maliput/api/rules/right_of_way_rule.h>
#include <maliput/api/rules/road_rulebook.h>
#include <maliput/api/rules/rule_registry.h>
#include <maliput/api/rules/traffic_light_book.h>
#include <maliput/api/rules/traffic_lights.h>
// TODO: Should be removed as SpeedLimitRule gets deprecated.
#include <maliput/api/rules/speed_limit_rule.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace maliput {
namespace api {
namespace bindings {

namespace py = pybind11;

void InitializeRulesNamespace(py::module* m) {
  auto rule_type = py::class_<rules::Rule>(*m, "Rule")
                       .def(py::init<const rules::Rule::Id&, const rules::Rule::TypeId&, const LaneSRoute&>(),
                            py::arg("id"), py::arg("type_id"), py::arg("zone"))
                       .def("id", &rules::Rule::id, py::return_value_policy::reference)
                       .def("type_id", &rules::Rule::type_id, py::return_value_policy::reference)
                       .def("zone", &rules::Rule::zone, py::return_value_policy::reference);

  py::class_<rules::Rule::Id>(rule_type, "Id")
      .def(py::init<std::string>())
      .def("__eq__", &rules::Rule::Id::operator==)
      .def("string", &rules::Rule::Id::string, py::return_value_policy::reference_internal)
      .def(py::detail::hash(py::self))
      .def("__repr__", [](const rules::Rule::Id& id) { return id.string(); });

  py::class_<rules::Rule::TypeId>(rule_type, "TypeId")
      .def(py::init<std::string>())
      .def("__eq__", &rules::Rule::TypeId::operator==)
      .def("string", &rules::Rule::TypeId::string, py::return_value_policy::reference_internal)
      .def(py::detail::hash(py::self))
      .def("__repr__", [](const api::rules::Rule::TypeId& type_id) { return type_id.string(); });

  py::class_<rules::Rule::State>(rule_type, "State")
      .def(py::init<>())
      .def(py::init<int, rules::Rule::RelatedRules, rules::Rule::RelatedUniqueIds>(), py::arg("severity"),
           py::arg("related_rules"), py::arg("related_unique_ids"))
      .def_readonly_static("kStrict", &rules::Rule::State::kStrict)
      .def_readonly_static("kBestEffort", &rules::Rule::State::kBestEffort)
      .def("__eq__", &rules::Rule::State::operator==)
      .def("__ne__", &rules::Rule::State::operator!=)
      .def_readwrite("severity", &rules::Rule::State::severity)
      .def_readwrite("related_rules", &rules::Rule::State::related_rules)
      .def_readwrite("related_unique_ids", &rules::Rule::State::related_unique_ids);

  auto discrete_value_rule_type =
      py::class_<rules::DiscreteValueRule, rules::Rule>(*m, "DiscreteValueRule")
          .def(py::init<const rules::Rule::Id&, const rules::Rule::TypeId&, const LaneSRoute&,
                        const std::vector<rules::DiscreteValueRule::DiscreteValue>&>(),
               py::arg("id"), py::arg("type_id"), py::arg("zone"), py::arg("values"))
          .def("states", &rules::DiscreteValueRule::states, py::return_value_policy::reference);

  py::class_<rules::DiscreteValueRule::DiscreteValue, rules::Rule::State>(discrete_value_rule_type, "DiscreteValue")
      .def(py::init<>())
      .def(py::init<int, rules::Rule::RelatedRules, rules::Rule::RelatedUniqueIds, std::string>(), py::arg("severity"),
           py::arg("related_rules"), py::arg("related_unique_ids"), py::arg("value"))
      .def("__eq__", &rules::DiscreteValueRule::DiscreteValue::operator==)
      .def("__ne__", &rules::DiscreteValueRule::DiscreteValue::operator!=)
      .def_readwrite("value", &rules::DiscreteValueRule::DiscreteValue::value);

  auto range_value_rule_type = py::class_<rules::RangeValueRule, rules::Rule>(*m, "RangeValueRule")
                                   .def(py::init<const rules::Rule::Id&, const rules::Rule::TypeId&, const LaneSRoute&,
                                                 const std::vector<rules::RangeValueRule::Range>&>(),
                                        py::arg("id"), py::arg("type_id"), py::arg("zone"), py::arg("ranges"))
                                   .def("states", &rules::RangeValueRule::states, py::return_value_policy::reference);

  py::class_<rules::RangeValueRule::Range, rules::Rule::State>(range_value_rule_type, "Range")
      .def(py::init<>())
      .def(py::init<int, rules::Rule::RelatedRules, rules::Rule::RelatedUniqueIds, std::string, double, double>(),
           py::arg("severity"), py::arg("related_rules"), py::arg("related_unique_ids"), py::arg("description"),
           py::arg("min"), py::arg("max"))
      .def("__eq__", &rules::RangeValueRule::Range::operator==)
      .def("__ne__", &rules::RangeValueRule::Range::operator!=)
      .def("__lt__", &rules::RangeValueRule::Range::operator<)
      .def_readwrite("description", &rules::RangeValueRule::Range::description)
      .def_readwrite("min", &rules::RangeValueRule::Range::min)
      .def_readwrite("max", &rules::RangeValueRule::Range::max);

  auto rule_registry_type =
      py::class_<rules::RuleRegistry>(*m, "RuleRegistry")
          .def(py::init<>())
          .def("RegisterRangeValueRule", &rules::RuleRegistry::RegisterRangeValueRule, py::arg("type_id"),
               py::arg("all_possible_ranges"))
          .def("RegisterDiscreteValueRule", &rules::RuleRegistry::RegisterDiscreteValueRule, py::arg("type_id"),
               py::arg("all_possible_values"))
          .def("RangeValueRuleTypes", &rules::RuleRegistry::RangeValueRuleTypes,
               py::return_value_policy::reference_internal)
          .def("DiscreteValueRuleTypes", &rules::RuleRegistry::DiscreteValueRuleTypes,
               py::return_value_policy::reference_internal)
          .def("GetPossibleStatesOfRuleType", &rules::RuleRegistry::GetPossibleStatesOfRuleType, py::arg("type_id"))
          .def("BuildRangeValueRule", &rules::RuleRegistry::BuildRangeValueRule, py::arg("id"), py::arg("type_id"),
               py::arg("zone"), py::arg("ranges"))
          .def("BuildDiscreteValueRule", &rules::RuleRegistry::BuildDiscreteValueRule, py::arg("id"),
               py::arg("type_id"), py::arg("zone"), py::arg("values"));

  py::class_<rules::RuleRegistry::QueryResult>(rule_registry_type, "QueryResult")
      .def(py::init<rules::Rule::TypeId, std::variant<rules::RuleRegistry::QueryResult::Ranges,
                                                      rules::RuleRegistry::QueryResult::DiscreteValues>>(),
           py::arg("type_id"), py::arg("rule_values"))
      .def_readwrite("type_id", &rules::RuleRegistry::QueryResult::type_id)
      .def_readwrite("rule_values", &rules::RuleRegistry::QueryResult::rule_values);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
  // @{ TODO: Should be removed as these types get deprecated.
  auto rowr_type =
      py::class_<rules::RightOfWayRule>(*m, "RightOfWayRule")
          .def("id", &rules::RightOfWayRule::id, py::return_value_policy::reference_internal)
          .def("zone", &rules::RightOfWayRule::zone, py::return_value_policy::reference_internal)
          .def("zone_type", &rules::RightOfWayRule::zone_type)
          .def("states", &rules::RightOfWayRule::states, py::return_value_policy::reference_internal)
          .def("is_static", &rules::RightOfWayRule::is_static)
          .def("static_state", &rules::RightOfWayRule::static_state, py::return_value_policy::reference_internal)
          .def("related_bulb_groups", &rules::RightOfWayRule::related_bulb_groups,
               py::return_value_policy::reference_internal);

  py::class_<rules::RightOfWayRule::Id>(rowr_type, "Id")
      .def(py::init<std::string>())
      .def("__eq__", &rules::RightOfWayRule::Id::operator==)
      .def("string", &rules::RightOfWayRule::Id::string, py::return_value_policy::reference_internal)
      .def(py::detail::hash(py::self))
      .def("__repr__", [](const rules::RightOfWayRule::Id& id) { return id.string(); });

  py::enum_<rules::RightOfWayRule::ZoneType>(rowr_type, "ZoneType")
      .value("kStopExcluded", rules::RightOfWayRule::ZoneType::kStopExcluded)
      .value("kStopAllowed", rules::RightOfWayRule::ZoneType::kStopAllowed)
      .export_values();

  auto rowrs_type =
      py::class_<rules::RightOfWayRule::State>(rowr_type, "State")
          .def(py::init<rules::RightOfWayRule::State::Id, rules::RightOfWayRule::State::Type,
                        const rules::RightOfWayRule::State::YieldGroup&>(),
               py::arg("id"), py::arg("type"), py::arg("yield_to"))
          .def("id", &rules::RightOfWayRule::State::id, py::return_value_policy::reference_internal)
          .def("type", &rules::RightOfWayRule::State::type)
          .def("yield_to", &rules::RightOfWayRule::State::yield_to, py::return_value_policy::reference_internal);

  py::class_<rules::RightOfWayRule::State::Id>(rowrs_type, "Id")
      .def(py::init<std::string>())
      .def("__eq__", &rules::RightOfWayRule::State::Id::operator==)
      .def("string", &rules::RightOfWayRule::State::Id::string, py::return_value_policy::reference_internal)
      .def(py::detail::hash(py::self))
      .def("__repr__", [](const rules::RightOfWayRule::State::Id& id) { return id.string(); });

  py::enum_<rules::RightOfWayRule::State::Type>(rowrs_type, "Type")
      .value("kGo", rules::RightOfWayRule::State::Type::kGo)
      .value("kStop", rules::RightOfWayRule::State::Type::kStop)
      .value("kStopThenGo", rules::RightOfWayRule::State::Type::kStopThenGo)
      .export_values();

  auto dur_type =
      py::class_<rules::DirectionUsageRule>(*m, "DirectionUsageRule").def("id", &rules::DirectionUsageRule::id);

  py::class_<rules::DirectionUsageRule::Id>(dur_type, "Id")
      .def(py::init<std::string>())
      .def("__eq__", &rules::DirectionUsageRule::Id::operator==)
      .def("string", &rules::DirectionUsageRule::Id::string, py::return_value_policy::reference_internal)
      .def(py::detail::hash(py::self))
      .def("__repr__", [](const rules::DirectionUsageRule::Id& id) { return id.string(); });

  auto slr_type = py::class_<rules::SpeedLimitRule>(*m, "SpeedLimitRule").def("id", &rules::SpeedLimitRule::id);

  py::class_<rules::SpeedLimitRule::Id>(slr_type, "Id")
      .def(py::init<std::string>())
      .def("__eq__", &rules::SpeedLimitRule::Id::operator==)
      .def("string", &rules::SpeedLimitRule::Id::string, py::return_value_policy::reference_internal)
      .def(py::detail::hash(py::self))
      .def("__repr__", [](const rules::SpeedLimitRule::Id& id) { return id.string(); });
  // @}

  auto road_rulebook_type =
      py::class_<rules::RoadRulebook>(*m, "RoadRulebook")
          .def("FindRules", &rules::RoadRulebook::FindRules, py::arg("ranges"), py::arg("tolerance"))
          .def("Rules", &rules::RoadRulebook::Rules)
          .def("GetRule",
               py::overload_cast<const rules::RightOfWayRule::Id&>(&rules::RoadRulebook::GetRule, py::const_),
               py::arg("id"))
          .def("GetRule",
               py::overload_cast<const rules::SpeedLimitRule::Id&>(&rules::RoadRulebook::GetRule, py::const_),
               py::arg("id"))
          .def("GetRule",
               py::overload_cast<const rules::DirectionUsageRule::Id&>(&rules::RoadRulebook::GetRule, py::const_),
               py::arg("id"))
          .def("GetDiscreteValueRule", &rules::RoadRulebook::GetDiscreteValueRule, py::arg("id"))
          .def("GetRangeValueRule", &rules::RoadRulebook::GetRangeValueRule, py::arg("id"));
#pragma GCC diagnostic pop

  py::class_<rules::RoadRulebook::QueryResults>(road_rulebook_type, "QueryResults")
      .def_readwrite("right_of_way", &rules::RoadRulebook::QueryResults::right_of_way)
      .def_readwrite("speed_limit", &rules::RoadRulebook::QueryResults::speed_limit)
      .def_readwrite("direction_usage", &rules::RoadRulebook::QueryResults::direction_usage)
      .def_readwrite("discrete_value_rules", &rules::RoadRulebook::QueryResults::discrete_value_rules)
      .def_readwrite("range_value_rules", &rules::RoadRulebook::QueryResults::range_value_rules);

  auto dvr_state_provider_type =
      py::class_<rules::DiscreteValueRuleStateProvider>(*m, "DiscreteValueRuleStateProvider")
          .def("GetState",
               py::overload_cast<const rules::Rule::Id&>(&rules::DiscreteValueRuleStateProvider::GetState, py::const_),
               py::arg("id"))
          .def("GetState",
               py::overload_cast<const RoadPosition&, const rules::Rule::TypeId&, double>(
                   &rules::DiscreteValueRuleStateProvider::GetState, py::const_),
               py::arg("road_position"), py::arg("rule_type"), py::arg("tolerance"));

  auto dvr_state_provider_state_result_type =
      py::class_<rules::DiscreteValueRuleStateProvider::StateResult>(dvr_state_provider_type, "StateResult")
          .def_readwrite("state", &rules::DiscreteValueRuleStateProvider::StateResult::state)
          .def_readwrite("next", &rules::DiscreteValueRuleStateProvider::StateResult::next);

  py::class_<rules::DiscreteValueRuleStateProvider::StateResult::Next>(dvr_state_provider_state_result_type, "Next")
      .def_readwrite("state", &rules::DiscreteValueRuleStateProvider::StateResult::Next::state)
      .def_readwrite("duration_until", &rules::DiscreteValueRuleStateProvider::StateResult::Next::duration_until);

  auto rvr_state_provider_type =
      py::class_<rules::RangeValueRuleStateProvider>(*m, "RangeValueRuleStateProvider")
          .def("GetState",
               py::overload_cast<const rules::Rule::Id&>(&rules::RangeValueRuleStateProvider::GetState, py::const_),
               py::arg("id"))
          .def("GetState",
               py::overload_cast<const RoadPosition&, const rules::Rule::TypeId&, double>(
                   &rules::RangeValueRuleStateProvider::GetState, py::const_),
               py::arg("road_position"), py::arg("rule_type"), py::arg("tolerance"));

  auto rvr_state_provider_state_result_type =
      py::class_<rules::RangeValueRuleStateProvider::StateResult>(rvr_state_provider_type, "StateResult")
          .def_readwrite("state", &rules::RangeValueRuleStateProvider::StateResult::state)
          .def_readwrite("next", &rules::RangeValueRuleStateProvider::StateResult::next);

  py::class_<rules::RangeValueRuleStateProvider::StateResult::Next>(rvr_state_provider_state_result_type, "Next")
      .def_readwrite("state", &rules::RangeValueRuleStateProvider::StateResult::Next::state)
      .def_readwrite("duration_until", &rules::RangeValueRuleStateProvider::StateResult::Next::duration_until);

  py::enum_<rules::BulbColor>(*m, "BulbColor")
      .value("kRed", rules::BulbColor::kRed)
      .value("kYellow", rules::BulbColor::kYellow)
      .value("kGreen", rules::BulbColor::kGreen);

  py::enum_<rules::BulbState>(*m, "BulbState")
      .value("kOff", rules::BulbState::kOff)
      .value("kOn", rules::BulbState::kOn)
      .value("kBlinking", rules::BulbState::kBlinking);

  py::enum_<rules::BulbType>(*m, "BulbType")
      .value("kRound", rules::BulbType::kRound)
      .value("kArrow", rules::BulbType::kArrow);

  m->def("BulbColorMapper", &rules::BulbColorMapper);
  m->def("BulbStateMapper", &rules::BulbStateMapper);
  m->def("BulbTypeMapper", &rules::BulbTypeMapper);

  // Partial bindings because of rules::Bulb::BoundingBox() default argument
  // when constructing a rules::Bulb yields a runtime error in at the module
  // import.
  auto bulb_type = py::class_<rules::Bulb>(*m, "Bulb");

  py::class_<rules::Bulb::BoundingBox>(bulb_type, "BoundingBox")
      .def(py::init<>())
      .def_readwrite("p_BMin", &rules::Bulb::BoundingBox::p_BMin)
      .def_readwrite("p_BMax", &rules::Bulb::BoundingBox::p_BMax);

  bulb_type
      .def(py::init<const rules::Bulb::Id&, const maliput::api::InertialPosition&, const maliput::api::Rotation&,
                    const rules::BulbColor&, const rules::BulbType&, const std::optional<double>&,
                    const std::optional<std::vector<rules::BulbState>>&, rules::Bulb::BoundingBox>(),
           py::arg("id"), py::arg("position_bulb_group"), py::arg("orientation_bulb_group"), py::arg("color"),
           py::arg("type"), py::arg("arrow_orientation_rad") = std::nullopt, py::arg("states") = std::nullopt,
           py::arg("bounding_box") = rules::Bulb::BoundingBox())
      .def("id", &rules::Bulb::id, py::return_value_policy::reference)
      .def("unique_id", &rules::Bulb::unique_id)
      .def("position_bulb_group", &rules::Bulb::position_bulb_group, py::return_value_policy::reference)
      .def("orientation_bulb_group", &rules::Bulb::orientation_bulb_group, py::return_value_policy::reference)
      .def("color", &rules::Bulb::color, py::return_value_policy::reference)
      .def("type", &rules::Bulb::type, py::return_value_policy::reference)
      .def("arrow_orientation_rad", &rules::Bulb::arrow_orientation_rad)
      .def("states", &rules::Bulb::states, py::return_value_policy::reference)
      .def("GetDefaultState", &rules::Bulb::GetDefaultState)
      .def("IsValidState", &rules::Bulb::IsValidState, py::return_value_policy::reference)
      .def("bounding_box", &rules::Bulb::bounding_box, py::return_value_policy::reference)
      .def("bulb_group", &rules::Bulb::bulb_group, py::return_value_policy::reference_internal);

  py::class_<rules::Bulb::Id>(bulb_type, "Id")
      .def(py::init<std::string>())
      .def("__eq__", &rules::Bulb::Id::operator==)
      .def("string", &rules::Bulb::Id::string, py::return_value_policy::reference_internal)
      .def(py::detail::hash(py::self))
      .def("__repr__", [](const rules::Bulb::Id& id) { return id.string(); });

  auto bulb_group_type =
      py::class_<rules::BulbGroup>(*m, "BulbGroup")
          // TODO(https://github.com/maliput/maliput_infrastructure/issues/225): Add constructor binding once it is
          // supported by pybind11.
          .def("id", &rules::BulbGroup::id, py::return_value_policy::reference)
          .def("unique_id", &rules::BulbGroup::unique_id)
          .def("position_traffic_light", &rules::BulbGroup::position_traffic_light, py::return_value_policy::reference)
          .def("orientation_traffic_light", &rules::BulbGroup::orientation_traffic_light,
               py::return_value_policy::reference)
          // TODO: the following binding might lead to leaks as it is explained in
          // https://github.com/pybind/pybind11/issues/637. We should look into the proposed solution.
          .def("bulbs", &rules::BulbGroup::bulbs, py::return_value_policy::reference)
          .def("GetBulb", &rules::BulbGroup::GetBulb, py::arg("id"), py::return_value_policy::reference_internal)
          .def("traffic_light", &rules::BulbGroup::traffic_light, py::return_value_policy::reference_internal);

  py::class_<rules::BulbGroup::Id>(bulb_group_type, "Id")
      .def(py::init<std::string>())
      .def("__eq__", &rules::BulbGroup::Id::operator==)
      .def("string", &rules::BulbGroup::Id::string, py::return_value_policy::reference_internal)
      .def(py::detail::hash(py::self))
      .def("__repr__", [](const rules::BulbGroup::Id& id) { return id.string(); });

  auto traffic_light_type =
      py::class_<rules::TrafficLight>(*m, "TrafficLight")
          // TODO(https://github.com/maliput/maliput_infrastructure/issues/225): Add constructor binding once it is
          // supported by pybind11.
          .def("id", &rules::TrafficLight::id, py::return_value_policy::reference)
          .def("position_road_network", &rules::TrafficLight::position_road_network, py::return_value_policy::reference)
          .def("orientation_road_network", &rules::TrafficLight::orientation_road_network,
               py::return_value_policy::reference)
          // TODO: the following binding might lead to leaks as it is explained in
          // https://github.com/pybind/pybind11/issues/637. We should look into the proposed solution.
          .def("bulb_groups", &rules::TrafficLight::bulb_groups, py::return_value_policy::reference)
          .def("GetBulbGroup", &rules::TrafficLight::GetBulbGroup, py::arg("id"),
               py::return_value_policy::reference_internal);

  py::class_<rules::TrafficLight::Id>(traffic_light_type, "Id")
      .def(py::init<std::string>())
      .def("__eq__", &rules::TrafficLight::Id::operator==)
      .def("string", &rules::TrafficLight::Id::string, py::return_value_policy::reference_internal)
      .def(py::detail::hash(py::self))
      .def("__repr__", [](const rules::TrafficLight::Id& id) { return id.string(); });

  py::class_<rules::UniqueBulbId, maliput::api::UniqueId>(*m, "UniqueBulbId")
      .def(py::init<>())
      .def(py::init<const rules::TrafficLight::Id&, const rules::BulbGroup::Id&, const rules::Bulb::Id&>(),
           py::arg("traffic_light_id"), py::arg("bulb_group_id"), py::arg("bulb_id"))
      .def("__eq__", &rules::UniqueBulbId::operator==)
      .def("string", &rules::UniqueBulbId::string, py::return_value_policy::reference_internal)
      .def(py::detail::hash(py::self))
      .def("__repr__", [](const rules::UniqueBulbId& id) { return id.string(); })
      .def("traffic_light_id", &rules::UniqueBulbId::traffic_light_id)
      .def("bulb_group_id", &rules::UniqueBulbId::bulb_group_id)
      .def("bulb_id", &rules::UniqueBulbId::bulb_id)
      .def_static("delimiter", []() { return rules::UniqueBulbId::delimiter(); });

  py::class_<rules::UniqueBulbGroupId, maliput::api::UniqueId>(*m, "UniqueBulbGroupId")
      .def(py::init<>())
      .def(py::init<const rules::TrafficLight::Id&, const rules::BulbGroup::Id&>(), py::arg("traffic_light_id"),
           py::arg("bulb_group_id"))
      .def("__eq__", &rules::UniqueBulbGroupId::operator==)
      .def("string", &rules::UniqueBulbGroupId::string, py::return_value_policy::reference_internal)
      .def(py::detail::hash(py::self))
      .def("__repr__", [](const rules::UniqueBulbGroupId& id) { return id.string(); })
      .def("traffic_light_id", &rules::UniqueBulbGroupId::traffic_light_id)
      .def("bulb_group_id", &rules::UniqueBulbGroupId::bulb_group_id)
      .def_static("delimiter", []() { return rules::UniqueBulbGroupId::delimiter(); });

  py::class_<rules::TrafficLightBook>(*m, "TrafficLightBook")
      .def("GetTrafficLight", &rules::TrafficLightBook::GetTrafficLight, py::arg("traffic_light_id"),
           py::return_value_policy::reference)
      .def("TrafficLights", &rules::TrafficLightBook::TrafficLights);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
  auto phase_type = py::class_<rules::Phase>(*m, "Phase")
                        .def(py::init<const rules::Phase::Id&, const rules::RuleStates&,
                                      const rules::DiscreteValueRuleStates&, std::optional<rules::BulbStates>>(),
                             py::arg("id"), py::arg("rule_states"), py::arg("discrete_value_rule_states"),
                             py::arg("bulb_states") = std::nullopt)
                        .def("id", &rules::Phase::id, py::return_value_policy::reference)
                        .def("rule_states", &rules::Phase::rule_states, py::return_value_policy::reference)
                        .def("discrete_value_rule_states", &rules::Phase::discrete_value_rule_states,
                             py::return_value_policy::reference)
                        .def("bulb_states", &rules::Phase::bulb_states, py::return_value_policy::reference);
#pragma GCC diagnostic pop

  py::class_<rules::Phase::Id>(phase_type, "Id")
      .def(py::init<std::string>())
      .def("__eq__", &rules::Phase::Id::operator==)
      .def("string", &rules::Phase::Id::string, py::return_value_policy::reference_internal)
      .def(py::detail::hash(py::self))
      .def("__repr__", [](const rules::Phase::Id& id) { return id.string(); });

  auto phase_ring_type =
      py::class_<rules::PhaseRing>(*m, "PhaseRing")
          .def(py::init<const rules::PhaseRing::Id&, const std::vector<rules::Phase>&,
                        const std::optional<
                            const std::unordered_map<rules::Phase::Id, std::vector<rules::PhaseRing::NextPhase>>>&>(),
               py::arg("id"), py::arg("phases"), py::arg("next_phases") = std::nullopt)
          .def("id", &rules::PhaseRing::id, py::return_value_policy::reference)
          .def("GetPhase", &rules::PhaseRing::GetPhase, py::arg("id"))
          .def("phases", &rules::PhaseRing::phases, py::return_value_policy::reference)
          .def("next_phases", &rules::PhaseRing::next_phases, py::return_value_policy::reference)
          .def("GetNextPhases", &rules::PhaseRing::GetNextPhases, py::arg("id"), py::return_value_policy::reference);

  py::class_<rules::PhaseRing::Id>(phase_ring_type, "Id")
      .def(py::init<std::string>())
      .def("__eq__", &rules::PhaseRing::Id::operator==)
      .def("string", &rules::PhaseRing::Id::string, py::return_value_policy::reference_internal)
      .def(py::detail::hash(py::self))
      .def("__repr__", [](const rules::PhaseRing::Id& id) { return id.string(); });

  py::class_<rules::PhaseRing::NextPhase>(phase_ring_type, "NextPhase")
      .def(py::init<rules::Phase::Id, std::optional<double>>(), py::arg("id"), py::arg("duration_until"))
      .def_readwrite("id", &rules::PhaseRing::NextPhase::id)
      .def_readwrite("duration_until", &rules::PhaseRing::NextPhase::duration_until);

  auto phase_provider_type = py::class_<rules::PhaseProvider>(*m, "PhaseProvider")
                                 .def("GetPhase", &rules::PhaseProvider::GetPhase, py::arg("id"));

  auto phase_provider_state_result_type = py::class_<rules::PhaseProvider::Result>(phase_provider_type, "Result")
                                              .def_readwrite("state", &rules::PhaseProvider::Result::state)
                                              .def_readwrite("next", &rules::PhaseProvider::Result::next);

  py::class_<rules::PhaseProvider::Result::Next>(phase_provider_state_result_type, "Next")
      .def_readwrite("state", &rules::PhaseProvider::Result::Next::state)
      .def_readwrite("duration_until", &rules::PhaseProvider::Result::Next::duration_until);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
  py::class_<rules::PhaseRingBook>(*m, "PhaseRingBook")
      .def("GetPhaseRings", &rules::PhaseRingBook::GetPhaseRings)
      .def("GetPhaseRing", &rules::PhaseRingBook::GetPhaseRing, py::arg("id"))
      .def("FindPhaseRing",
           py::overload_cast<const rules::RightOfWayRule::Id&>(&rules::PhaseRingBook::FindPhaseRing, py::const_),
           py::arg("rule_id"))
      .def("FindPhaseRing", py::overload_cast<const rules::Rule::Id&>(&rules::PhaseRingBook::FindPhaseRing, py::const_),
           py::arg("rule_id"));
#pragma GCC diagnostic pop
}

}  // namespace bindings
}  // namespace api
}  // namespace maliput

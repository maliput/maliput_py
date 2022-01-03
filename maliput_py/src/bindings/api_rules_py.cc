#include "bindings/api_rules_py.h"

#include <maliput/api/rules/discrete_value_rule.h>
#include <maliput/api/rules/rule.h>
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
      .def("__repr__", [](const rules::Rule::Id& id) { return id.string(); });

  py::class_<rules::Rule::TypeId>(rule_type, "TypeId")
      .def(py::init<std::string>())
      .def("__eq__", &rules::Rule::TypeId::operator==)
      .def("string", &rules::Rule::TypeId::string, py::return_value_policy::reference_internal)
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
               py::arg("id"), py::arg("type_id"), py::arg("zone"), py::arg("value"))
          .def("values", &rules::DiscreteValueRule::values, py::return_value_policy::reference);

  py::class_<rules::DiscreteValueRule::DiscreteValue, rules::Rule::State>(discrete_value_rule_type, "DiscreteValue")
      .def(py::init<>())
      .def(py::init<int, rules::Rule::RelatedRules, rules::Rule::RelatedUniqueIds, std::string>(), py::arg("severity"),
           py::arg("related_rules"), py::arg("related_unique_ids"), py::arg("value"))
      .def("__eq__", &rules::DiscreteValueRule::DiscreteValue::operator==)
      .def("__ne__", &rules::DiscreteValueRule::DiscreteValue::operator!=)
      .def_readwrite("value", &rules::DiscreteValueRule::DiscreteValue::value);
}

}  // namespace bindings
}  // namespace api
}  // namespace maliput

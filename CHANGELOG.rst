^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package maliput_py
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

0.1.0 (2022-06-16)
------------------
* Updates package.xml
* Suppresses old-rule-api-related deprecation warnings. (`#62 <https://github.com/maliput/maliput_py/issues/62>`_)
* Depends on pybind11 package via rosdep. (`#61 <https://github.com/maliput/maliput_py/issues/61>`_)
* Uses ros-action-ci in build.yaml workflow. (`#59 <https://github.com/maliput/maliput_py/issues/59>`_)
* Moves package to root (`#60 <https://github.com/maliput/maliput_py/issues/60>`_)
* Updates license. (`#58 <https://github.com/maliput/maliput_py/issues/58>`_)
* Removes dashing CI. (`#57 <https://github.com/maliput/maliput_py/issues/57>`_)
* Added a binding in RoadPosition for ToInertialPosition method (`#56 <https://github.com/maliput/maliput_py/issues/56>`_)
* Adds IntersectionBook::FindIntersection(inertial_pos) binding. (`#55 <https://github.com/maliput/maliput_py/issues/55>`_)
* Merge pull request `#54 <https://github.com/maliput/maliput_py/issues/54>`_ from ToyotaResearchInstitute/voldivh/value_range_method_to_state
* [FEAT]: Changed values() and ranges() method from Rules to states()
* Adds bindings for new GetState method in the state providers. (`#53 <https://github.com/maliput/maliput_py/issues/53>`_)
* Adds BUILD_DOCS flag as opt-in flag (`#52 <https://github.com/maliput/maliput_py/issues/52>`_)
* Adds workflow_dispatch to other workflows. (`#51 <https://github.com/maliput/maliput_py/issues/51>`_)
* Adds PhaseRingBook bindings (`#48 <https://github.com/maliput/maliput_py/issues/48>`_)
* Tests maliput::api interfaces (`#47 <https://github.com/maliput/maliput_py/issues/47>`_)
* Completes RoadNetwork bindings (`#46 <https://github.com/maliput/maliput_py/issues/46>`_)
* Adds IntersectionBook (`#45 <https://github.com/maliput/maliput_py/issues/45>`_)
* Adds CI badges (`#50 <https://github.com/maliput/maliput_py/issues/50>`_)
* Adds Intersection bindings (`#44 <https://github.com/maliput/maliput_py/issues/44>`_)
  Co-authored-by: Franco Cipollone <53065142+francocipollone@users.noreply.github.com>
* Adds PhaseProvider bindings (`#43 <https://github.com/maliput/maliput_py/issues/43>`_)
* Adds PhaseRing bindings (`#42 <https://github.com/maliput/maliput_py/issues/42>`_)
* Adds Phase bindings. (`#41 <https://github.com/maliput/maliput_py/issues/41>`_)
* Adds bindings for UniqueBulbId, UniqueBulbGroupId and fixes hashing in other Ids (`#40 <https://github.com/maliput/maliput_py/issues/40>`_)
* Adds TrafficLight bindings. (`#39 <https://github.com/maliput/maliput_py/issues/39>`_)
* Adds BulbGroup bindings (`#38 <https://github.com/maliput/maliput_py/issues/38>`_)
* Adds Bulb bindings. (`#37 <https://github.com/maliput/maliput_py/issues/37>`_)
* Adds bindings for some Bulb related types (`#36 <https://github.com/maliput/maliput_py/issues/36>`_)
* Adds bindings for RuleStateProviders. (`#35 <https://github.com/maliput/maliput_py/issues/35>`_)
* Adds RoadRulebook bindings. (`#34 <https://github.com/maliput/maliput_py/issues/34>`_)
* Adds bindings for RuleRegistry. (`#33 <https://github.com/maliput/maliput_py/issues/33>`_)
* Adds DiscreteValueRule and RangeValueRule binding (`#32 <https://github.com/maliput/maliput_py/issues/32>`_)
* Adds bindings for Rule, Rule::State and UniqueId (`#30 <https://github.com/maliput/maliput_py/issues/30>`_)
* Replaces push by workflow_dispatch event in gcc build. (`#29 <https://github.com/maliput/maliput_py/issues/29>`_)
* Completes Lane API bindinds and adds RBounds, HBounds and IsoLaneVelocity. (`#28 <https://github.com/maliput/maliput_py/issues/28>`_)
* Adds LaneEndSet and BranchPoint (`#27 <https://github.com/maliput/maliput_py/issues/27>`_)
* Adds LaneEnd binding. (`#26 <https://github.com/maliput/maliput_py/issues/26>`_)
* Adds python bindings for SRange, LaneSRange and LaneSRoute. (`#25 <https://github.com/maliput/maliput_py/issues/25>`_)
* Extends LanePosition and ***Id python interface (`#24 <https://github.com/maliput/maliput_py/issues/24>`_)
* Extends python interface of some maliput.api entities. (`#23 <https://github.com/maliput/maliput_py/issues/23>`_)
* Adds MaliputPluginManager::ListPlugins binding. (`#22 <https://github.com/maliput/maliput_py/issues/22>`_)
* Documents maliput python interface. (`#19 <https://github.com/maliput/maliput_py/issues/19>`_)
* Tests maliput::api bindings. (`#17 <https://github.com/maliput/maliput_py/issues/17>`_)
* Fixes binding to CreateRoadNetworkFromPlugin method. (`#15 <https://github.com/maliput/maliput_py/issues/15>`_)
* Set up linker properly when using clang. (`#13 <https://github.com/maliput/maliput_py/issues/13>`_)
* Removes ament_target_dependencies  (`#12 <https://github.com/maliput/maliput_py/issues/12>`_)
* Use drake branch of pybind11, use 20.04 in CI (`#9 <https://github.com/maliput/maliput_py/issues/9>`_)
* Use newer revision of pybind11 (`#10 <https://github.com/maliput/maliput_py/issues/10>`_)
* rosdep update --include-eol-distros (`#11 <https://github.com/maliput/maliput_py/issues/11>`_)
* Fix include style part 2: rearrange headers (`#8 <https://github.com/maliput/maliput_py/issues/8>`_)
* Fix include style part 1: use <> for maliput, pybind11 includes (`#7 <https://github.com/maliput/maliput_py/issues/7>`_)
* Upgrade ros-tooling to v0.2.1 (`#6 <https://github.com/maliput/maliput_py/issues/6>`_)
* Rename maliput documentation (`#5 <https://github.com/maliput/maliput_py/issues/5>`_)
* Switch ament_cmake_doxygen to main. (`#4 <https://github.com/maliput/maliput_py/issues/4>`_)
* Optimizes scan-build run in CI. (`#3 <https://github.com/maliput/maliput_py/issues/3>`_)
* Add changelog template (`#2 <https://github.com/maliput/maliput_py/issues/2>`_)
* Split maliput and maliput_py
* Installs git in workflows.
* Adds vcs checkout to matching branch.
* Adds various config and buid files that were not part of the migration.
* Adds CI configuration
* Moves maliput_py contents into maliput_py folder.
* Uses ament_cmake_flake8 package instead of pycodestyle. (`#383 <https://github.com/maliput/maliput_py/issues/383>`_)
* Adds python3 dependency to maliput_py's package.xml. (`#382 <https://github.com/maliput/maliput_py/issues/382>`_)
* Adds a python binding function to easily create a RoadNetwork (`#380 <https://github.com/maliput/maliput_py/issues/380>`_)
* Implements a Plugin architecture (`#377 <https://github.com/maliput/maliput_py/issues/377>`_)
* Rename ToGeoPosition and GeoPosition by ToInertialPosition and InertialPosition (`#376 <https://github.com/maliput/maliput_py/issues/376>`_)
* Adds pylint to maliput_py package. (`#375 <https://github.com/maliput/maliput_py/issues/375>`_)
* Move bindings to another package. (`#374 <https://github.com/maliput/maliput_py/issues/374>`_)
* Initial commit
* Contributors: Agustin Alba Chicar, Chien-Liang Fok, Franco Cipollone, Geoffrey Biggs, Steve Peters, Voldivh

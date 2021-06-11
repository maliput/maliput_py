# `maliput_py`

Python bindings for `maliput` which rely on `pybind11`.

## Build

1. Setup a development workspace as described [here](https://github.com/ToyotaResearchInstitute/maliput_documentation/blob/main/docs/installation_quickstart.rst).

2. Build `maliput_py` packages and their dependencies:

   ```sh
   colcon build --packages-up-to maliput_py
   ```
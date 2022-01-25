| GCC | Sanitizers(Clang) | Scan-Build |
| --------- | --------- | -------- |
|[![gcc](https://github.com/ToyotaResearchInstitute/maliput_py/actions/workflows/build.yml/badge.svg)](https://github.com/ToyotaResearchInstitute/maliput_py/actions/workflows/build.yml) | [![clang](https://github.com/ToyotaResearchInstitute/maliput_py/actions/workflows/sanitizers.yml/badge.svg)](https://github.com/ToyotaResearchInstitute/maliput_py/actions/workflows/sanitizers.yml) | [![scan_build](https://github.com/ToyotaResearchInstitute/maliput_py/actions/workflows/scan_build.yml/badge.svg)](https://github.com/ToyotaResearchInstitute/maliput_py/actions/workflows/scan_build.yml) |

# `maliput_py`

Python bindings for `maliput` which rely on `pybind11`.

## Build

1. Setup a development workspace as described [here](https://github.com/ToyotaResearchInstitute/maliput_documentation/blob/main/docs/installation_quickstart.rst).

2. Build `maliput_py` packages and their dependencies:

   ```sh
   colcon build --packages-up-to maliput_py
   ```

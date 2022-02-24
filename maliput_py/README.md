![gcc](https://github.com/ToyotaResearchInstitute/maliput_py/actions/workflows/build.yml/badge.svg)

# maliput_py

Maliput Python bindings.

## Build

1. Setup a maliput_py (or a wider maliput) development workspace as described [here](https://github.com/ToyotaResearchInstitute/maliput_documentation/blob/main/docs/installation_quickstart.rst).
2. Build maliput_py packages and their dependencies:
   ```sh
   colcon build --packages-up-to maliput_py
   ```

   **Note**: To build documentation a `-BUILD_DOCS` cmake flag is required:
   ```sh
   colcon build --packages-up-to maliput_py --cmake-args " -DBUILD_DOCS=On"
   ```

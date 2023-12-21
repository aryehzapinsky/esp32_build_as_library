#!/usr/bin/env bash

# Setup
/BuildEspAsLibrary/external_components/esp-idf/tools/idf_tools.py install
/BuildEspAsLibrary/external_components/esp-idf/tools/idf_tools.py install-python-env
python -m pip install esp-idf-kconfig
/root/.espressif/python_env/idf5.3_py3.10_env/bin/pip3 install esp-idf-kconfig

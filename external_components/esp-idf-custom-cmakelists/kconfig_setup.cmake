# python -m pip install esp-idf-kconfig
execute_process(COMMAND "python -m kconfgen --kconfig external_components/Kconfig --output header external_components/sdkconfig.h")
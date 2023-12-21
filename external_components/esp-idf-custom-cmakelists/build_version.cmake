
include(/BuildEspAsLibrary/external_components/esp-idf/tools/cmake/third_party/GetGitRevisionDescription.cmake)

git_describe(idf_ver_git "/BuildEspAsLibrary/external_components/esp-idf" "--match=v*.*")
# cut IDF_VER to required 32 characters.
string(SUBSTRING "${idf_ver_git}" 0 31 idf_ver)

include(CMakePrintHelpers)
cmake_print_variables(idf_ver)
#idf_build_set_property(COMPILE_DEFINITIONS "IDF_VER=\"${idf_ver}\"" APPEND)

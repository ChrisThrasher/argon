include(FetchContent)

FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v${Catch2_FIND_VERSION}
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(Catch2)
set_target_properties(Catch2 PROPERTIES COMPILE_OPTIONS "" EXPORT_COMPILE_COMMANDS OFF)
set_target_properties(Catch2WithMain PROPERTIES EXPORT_COMPILE_COMMANDS OFF)
target_compile_features(Catch2 PRIVATE cxx_std_17)

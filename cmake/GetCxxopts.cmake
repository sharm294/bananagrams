include(FetchContent)
FetchContent_Declare(
    cxxopts
    GIT_SHALLOW    TRUE
    GIT_REPOSITORY "https://github.com/jarro2783/cxxopts"
    GIT_TAG        "v3.0.0"
)

FetchContent_MakeAvailable(cxxopts)

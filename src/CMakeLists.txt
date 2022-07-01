include(GetCxxopts)

add_subdirectory(bananagrams)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE cxxopts bananagrams)
target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR}/src)

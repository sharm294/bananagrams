include(GetCxxopts)

add_subdirectory(bananagrams)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE cxxopts libbananagrams)
target_include_directories(main PRIVATE ${PROJECT_INCLUDE_DIRS})

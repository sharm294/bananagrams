include(CTest)

add_executable(graph_test graph.cpp)
target_link_libraries(graph_test PRIVATE bananagrams)
target_include_directories(graph_test PRIVATE ${PROJECT_SOURCE_DIR}/src)

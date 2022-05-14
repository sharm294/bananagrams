include(GetCatch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(CTest)
include(Catch)

add_executable(dictionary_test dictionary.cpp)
target_link_libraries(dictionary_test PRIVATE libbananagrams Catch2::Catch2)
target_include_directories(dictionary_test PRIVATE ${PROJECT_SOURCE_DIR}/src)

add_executable(board_test board.cpp)
target_link_libraries(board_test PRIVATE libbananagrams)
target_include_directories(board_test PRIVATE ${PROJECT_SOURCE_DIR}/src)

catch_discover_tests(dictionary_test)

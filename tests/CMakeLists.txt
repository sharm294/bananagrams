include(GetCatch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(CTest)
include(Catch)

add_executable(dictionary_test dictionary.cpp)
target_link_libraries(dictionary_test PRIVATE libbananagrams Catch2::Catch2)
target_include_directories(dictionary_test PRIVATE ${PROJECT_INCLUDE_DIRS})

add_executable(board_test board.cpp)
target_link_libraries(board_test PRIVATE libbananagrams)
target_include_directories(board_test PRIVATE ${PROJECT_INCLUDE_DIRS})

add_executable(bananagrams_test bananagrams.cpp)
target_link_libraries(bananagrams_test PRIVATE libbananagrams)
target_include_directories(bananagrams_test PRIVATE ${PROJECT_INCLUDE_DIRS})

add_executable(bananagrams_c_test bananagrams.c)
target_link_libraries(bananagrams_c_test PRIVATE libbananagrams)
target_include_directories(bananagrams_c_test PRIVATE ${PROJECT_INCLUDE_DIRS})

catch_discover_tests(dictionary_test)

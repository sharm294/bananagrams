include(CTest)

add_executable(database_test database.cpp)
target_link_libraries(database_test PRIVATE $<TARGET_OBJECTS:database>)
target_include_directories(database_test PRIVATE ${PROJECT_SOURCE_DIR}/src)

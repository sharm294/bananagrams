list(APPEND files
    bananagrams
    board
    charmap
    dictionary
    node
    play
)

list(APPEND object_files)

foreach(file ${files})
    add_library(${file} OBJECT ${file}.cpp)
    target_include_directories(${file} PRIVATE ${PROJECT_INCLUDE_DIRS})
    list(APPEND object_files $<TARGET_OBJECTS:${file}>)
endforeach()

add_library(libbananagrams SHARED ${object_files})
set_target_properties(libbananagrams PROPERTIES OUTPUT_NAME bananagrams)
target_link_libraries(libbananagrams PRIVATE ${files})

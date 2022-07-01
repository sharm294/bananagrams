list(APPEND files
    board
    charmap
    dictionary
    node
    play
)

list(APPEND object_files)

foreach(file ${files})
    add_library(${file} OBJECT ${file}.cpp)
    list(APPEND object_files $<TARGET_OBJECTS:${file}>)
endforeach()

add_library(bananagrams SHARED ${object_files})
target_link_libraries(bananagrams PRIVATE ${files})

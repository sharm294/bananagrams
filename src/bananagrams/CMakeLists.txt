list(APPEND files
    bananagrams
    board
    charmap
    dictionary
    node
)

list(APPEND object_files)

foreach(file ${files})
    add_library(${file} OBJECT ${file}.cpp)
    list(APPEND object_files $<TARGET_OBJECTS:${file}>)
endforeach()

add_library(libbananagrams INTERFACE)
target_link_libraries(libbananagrams INTERFACE
    ${files}
    ${object_files}
)

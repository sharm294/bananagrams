list(APPEND files
    graph
    node
)

list(APPEND object_files)

foreach(file ${files})
    add_library(${file} OBJECT ${file}.cpp)
    list(APPEND object_files $<TARGET_OBJECTS:${file}>)
endforeach()

add_library(bananagrams INTERFACE)
target_link_libraries(bananagrams INTERFACE
    ${files}
    ${object_files}
)

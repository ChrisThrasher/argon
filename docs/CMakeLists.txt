find_package(Doxygen 1.8)

if(NOT Doxygen_FOUND)
    return()
endif()

set(DOXYGEN_GENERATE_TREEVIEW TRUE)
doxygen_add_docs(docs ${PROJECT_SOURCE_DIR}/include)

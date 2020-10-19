file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/WateringMachine/Middleware/*.h" "${CMAKE_SOURCE_DIR}/src/WateringMachine/Middleware/*.cpp"  )
add_library(Middleware STATIC ${SOURCES})
set_target_properties(Middleware PROPERTIES LINKER_LANGUAGE CXX)
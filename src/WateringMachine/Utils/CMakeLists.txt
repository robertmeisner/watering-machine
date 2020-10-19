file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/WateringMachine/Utils/*.h" "${CMAKE_SOURCE_DIR}/src/WateringMachine/Utils/*.cpp"  )
add_library(Utils STATIC ${SOURCES})
set_target_properties(Utils PROPERTIES LINKER_LANGUAGE CXX)
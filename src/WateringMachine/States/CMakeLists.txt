file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/WateringMachine/States/*.h" "${CMAKE_SOURCE_DIR}/src/WateringMachine/States/*.cpp" )
add_library(States STATIC ${SOURCES})
set_target_properties(States PROPERTIES LINKER_LANGUAGE CXX)
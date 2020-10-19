file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/WateringMachine/*.h" "${CMAKE_SOURCE_DIR}/src/WateringMachine/*.cpp" )
add_library(WateringMachine STATIC ${SOURCES})
target_link_libraries(WateringMachine Components States Middleware Utils)
set_target_properties(WateringMachine PROPERTIES LINKER_LANGUAGE CXX)
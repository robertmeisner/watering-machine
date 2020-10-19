# INSPIRED BY 
# https://github.com/Pseudomanifold/Aleph/blob/53226a3ffca7b88dd81bfd748c3474bb8367ff1c/tests/CMakeLists.txt




ADD_EXECUTABLE( Light_unitest  "${CMAKE_CURRENT_SOURCE_DIR}/WateringMachine/Components/Light_unitest.cpp")
set_target_properties(Light_unitest PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Light_unitest Components Utils States Middleware)

ADD_EXECUTABLE( WateringMachine_unitest  "${CMAKE_CURRENT_SOURCE_DIR}/WateringMachine/Components/WateringMachine_unitest.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/helpers/MiddlewareTest.cpp" )
set_target_properties(WateringMachine_unitest PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(WateringMachine_unitest WateringMachine Components Utils States Middleware)

#file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/WateringMachine/*.h" "${CMAKE_SOURCE_DIR}/src/WateringMachine/*.cpp"  )
#target_sources(Light_unitest PRIVATE ${SOURCES})

ADD_TEST( Light   Light_unitest )
ADD_TEST( WateringMachine   WateringMachine_unitest )


# https://stackoverflow.com/questions/40227333/cmake-setup-multiple-projects-and-dependiencies-between-them
# https://stackoverflow.com/questions/6921695/how-can-i-build-a-c-project-with-multiple-interdependent-subdirectories
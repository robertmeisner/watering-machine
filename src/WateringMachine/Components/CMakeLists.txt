#set(HEADER_FILES ${YOUR_DIRECTORY}/file1.h ${YOUR_DIRECTORY}/file2.h)
#add_library(mylib libsrc.cpp ${HEADER_FILES})
#target_include_directories(mylib PRIVATE ${YOUR_DIRECTORY})
#add_executable(myexec execfile.cpp ${HEADER_FILES})
#target_include_directories(myexec PRIVATE ${YOUR_DIRECTORY})
#ADD_DEFINITIONS(-DGC_NOT_DLL)
#set(HEADER_FILES ${CMAKE_SOURCE_DIR}/src/WateringMachine/Components/StateMachineInterfaces/SwitchStateMachine.h ${CMAKE_SOURCE_DIR}/src/WateringMachine/Components/SimpleSwitch.h)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/WateringMachine/Components/*.h" "${CMAKE_SOURCE_DIR}/src/WateringMachine/Components/*.cpp" )
add_library(Components STATIC ${SOURCES})
set_target_properties(Components PROPERTIES LINKER_LANGUAGE CXX)


#target_include_directories(Light PUBLIC ${CMAKE_SOURCE_DIR}/src/WateringMachine/Components/StateMachineInterfaces ${CMAKE_SOURCE_DIR}/src/WateringMachine/Components)
cmake_minimum_required(VERSION 3.17.0)
project(watering-machine VERSION 0.1.0 LANGUAGES C CXX)

########################################################################


########################################################################
# Macros and additional flags
########################################################################

INCLUDE( CheckCXXCompilerFlag )
FILE( GLOB filenames "cmake/Macros/*.cmake" )
FOREACH( filename ${filenames} ) 
  INCLUDE( ${filename} )
  message(${filename})
ENDFOREACH()

ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wall" )
ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wconversion" )
ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wextra" )
ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wnon-virtual-dtor" )
ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wold-style-cast" )
ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Woverloaded-virtual" )
ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wself-init" )
ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wunsafe-loop-optimization" )
ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-pedantic" )



########################################################################
# Include directories
######################################################################## 
INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/src/WateringMachine
  ${CMAKE_SOURCE_DIR}/src/WateringMachine/Components
  ${CMAKE_SOURCE_DIR}/src/WateringMachine/Components/StateMachineInterfaces
  ${CMAKE_SOURCE_DIR}/src/WateringMachine/Middleware
  ${CMAKE_SOURCE_DIR}/src/WateringMachine/Middleware/MQTT
  ${CMAKE_SOURCE_DIR}/src/WateringMachine/Middleware/Logging
  ${CMAKE_SOURCE_DIR}/src/WateringMachine/States
  ${CMAKE_SOURCE_DIR}/src/WateringMachine/Utils
  ${CMAKE_SOURCE_DIR}/libraries
)

ADD_SUBDIRECTORY( src/WateringMachine/Components )
ADD_SUBDIRECTORY( src/WateringMachine/Utils )
ADD_SUBDIRECTORY( src/WateringMachine/States )
ADD_SUBDIRECTORY( src/WateringMachine/Middleware )
ADD_SUBDIRECTORY( src/WateringMachine )

# Tests
########################################################################

include(CTest)
# Enable testing globally. Individual tests may be found in the `tests`
# subdirectory of the repository.
ENABLE_TESTING()

ADD_SUBDIRECTORY( tests ) 

add_library(watering-machine src/WateringMachine/WateringMachine.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


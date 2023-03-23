#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
project(mdtsim)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})

message ("the project is: " ${PROJECT_SOURCE_DIR})

#----------------------------------------------------------------------------
# Find HepMC (required package)
#
find_package(HepMC REQUIRED)

#----------------------------------------------------------------------------
# Find Pythia6 (optional package)
#
find_package(Pythia6 QUIET)
if(PYTHIA6_FOUND)
  message(STATUS "G4 Examples: Pythia6 found. --> HepMCEx01 example with Pythia6 enabled.") 
  add_definitions(-DG4LIB_USE_PYTHIA) 
else()
  set(PYTHIA6_LIBRARIES "")  
endif()

#----------------------------------------------------------------------------
# Find ROOT
#
find_package(ROOT REQUIRED)
if(ROOT_FOUND)
  message("ROOT found")
else()
  message("ROOT NOT found")
endif()

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR}
                    ${HEPMC_INCLUDE_DIR}
		    ${ROOT_INCLUDE_DIRS} )

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cxx)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(mdtsim ${sources} ${headers})
target_link_libraries(tksim ${Geant4_LIBRARIES} 
                      ${HEPMC_LIBRARIES} 
                      ${HEPMC_FIO_LIBRARIES} ${PYTHIA6_LIBRARIES} ${ROOT_Core_LIBRARY} ${ROOT_Tree_LIBRARY} ${ROOT_Math_Library})


#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS mdtsim DESTINATION ${PROJECT_SOURCE_DIR}/../run)

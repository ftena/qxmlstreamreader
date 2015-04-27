####################################
####   specific parameters
####################################

## application name
set( APP_NAME "qxml" )

## project name
project( ${APP_NAME} )

## require a minimum version of CMake
CMAKE_MINIMUM_REQUIRED ( VERSION 2.6 FATAL_ERROR )

## add definitions, compiler switches, etc.
ADD_DEFINITIONS( -Wall -O2 )
SET( CMAKE_CXX_FLAGS -g )

## include (or not) the full compiler output
SET( CMAKE_VERBOSE_MAKEFILE OFF )

# find Qt
find_package(Qt5Core REQUIRED)
find_package(Qt5Xml REQUIRED)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# The AUTOUIC target property controls whether cmake(1) inspects the
# C++ files in the target to determine if they require uic to be run,
# and to create rules to execute uic at the appropriate time.
set(CMAKE_AUTOUIC ON)

## find boost package
find_package( Boost 1.55 COMPONENTS program_options REQUIRED )

## include directories
include_directories ( 
	${Boost_INCLUDE_DIRS}
)

## sources
file( GLOB MAIN_SRC *.cpp )
set( SOURCES ${MAIN_SRC} )

## executable
add_executable( ${APP_NAME} ${SOURCES} )

## link
target_link_libraries( ${APP_NAME} ${Boost_LIBRARIES} Qt5::Xml )


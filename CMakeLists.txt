cmake_minimum_required(VERSION 3.15...3.20)
project(FlightSim LANGUAGES CXX)

# Compiler Options
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_options(/D_HAS_AUTO_PTR_ETC=1)
    set(LIB_DIR "C:/Program Files/prti1516e/lib/vc141_64")
    set(FEDERATE_LIBS "librti1516e64" "libfedtime1516e64")
endif()

# Add the include directories for Pitch headers
include_directories("C:/Program Files/prti1516e/include")

# Add the library directory for Pitch libraries (if necessary)
link_directories("C:/Program Files/prti1516e/lib/vc141_64")

# List your header and source files
set(HEADER_FILES
    src/Debug.h
    src/baseFederate.h
    src/StringUtils.h
    src/DataInterface.h
    src/BoxObject.h
)

# Add main.cpp file of project root directory as source file
set(SOURCES 
    src/main.cpp
    src/Debug.cpp
    src/baseFederate.cpp
    src/StringUtils.cpp
    src/BoxObject.cpp
)

# Create a shared library (DLL) with the given sources
add_library(hla_plugin SHARED ${HEADER_FILES} ${SOURCES})
# Add the main.cpp file to the project
add_executable(test ${HEADER_FILES} ${SOURCES})

target_link_libraries(hla_plugin "C:/Program Files/prti1516e/lib/vc141_64/librti1516e64.lib")
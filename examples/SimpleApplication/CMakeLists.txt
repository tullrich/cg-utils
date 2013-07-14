
file(GLOB SIMPLEAPPLICATION_SRCFILES "src/*.cpp")

set (EXECUTABLE_OUTPUT_PATH ${CGUTILS_SAMPLE_OUTPUT_DIR})

# -------------------------------------------------------------
# Build                  
# -------------------------------------------------------------
add_executable(SimpleApplication ${SIMPLEAPPLICATION_SRCFILES})
TARGET_LINK_LIBRARIES(SimpleApplication ${CGUTILS_SAMPLE_LIBRARIES})

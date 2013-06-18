cmake_minimum_required (VERSION 2.6)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -lboost_system -lboost_filesystem -lboost_thread -llua -ldl -std=c++11")

project (cgutils)

# -------------------------------------------------------------
# Project Specific Variables                                   
# -------------------------------------------------------------
set (CGUTILS_VERSION_MAJOR 1)
set (CGUTILS_VERSION_MINOR 0)
set (CGUTILS_SRCS_DIR src)
set (CGUTILS_INCLUDE_DIR include)
set (CGUTILS_CMAKE_DIR cmake)

# -------------------------------------------------------------
# Source Tree Variables                       
# -------------------------------------------------------------
file(GLOB CGUTILS_SRCFILES "${CGUTILS_SRCS_DIR}/*.cpp")
include_directories("${CGUTILS_INCLUDE_DIR}")

# -------------------------------------------------------------
# FreeImage Dependency Tracking                         
# -------------------------------------------------------------
INCLUDE(${CGUTILS_CMAKE_DIR}/FindFreeImage.cmake)
IF(FREEIMAGE_FOUND)
	SET(HAVE_FREEIMAGE ${FREEIMAGE_FOUND} CACHE BOOL "Set to TRUE if FreeImage is found, FALSE otherwise")
	MESSAGE(STATUS "Looking for FreeImage - found")
ELSE(FREEIMAGE_FOUND)
	MESSAGE(FATAL_ERROR "Looking for FreeImage - not found")
ENDIF(FREEIMAGE_FOUND)
SET(LIBS ${LIBS} ${FREEIMAGE_LIBRARIES})
INCLUDE_DIRECTORIES(${FREEIMAGE_INCLUDE_PATH})

# -------------------------------------------------------------
# Boost Dependency Tracking                         
# -------------------------------------------------------------
FIND_PACKAGE( Boost COMPONENTS program_options REQUIRED )
IF (Boost_FOUND)
	MESSAGE(STATUS "Looking for Boost - found")
ELSE (Boost_FOUND)
	MESSAGE(FATAL_ERROR "Looking for Boost - not found")
ENDIF(Boost_FOUND)
SET(LIBS ${LIBS} ${Boost_LIBRARIES})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

# -------------------------------------------------------------
# Assimp Dependency Tracking                         
# -------------------------------------------------------------
INCLUDE( ${CGUTILS_CMAKE_DIR}/FindAssimp.cmake )
IF (ASSIMP_FOUND)
	MESSAGE(STATUS "Looking for Assimp - found")
ELSE (ASSIMP_FOUND)
	MESSAGE(FATAL_ERROR "Looking for Assimp - not found")
ENDIF(ASSIMP_FOUND)
SET(LIBS ${LIBS} ${ASSIMP_LIBRARY})
INCLUDE_DIRECTORIES(${ASSIMP_INCLUDE_DIR})

# -------------------------------------------------------------
# GLM Dependency Tracking                         
# -------------------------------------------------------------
INCLUDE( ${CGUTILS_CMAKE_DIR}/FindGLM.cmake )
IF (GLM_FOUND)
	MESSAGE(STATUS "Looking for GLM - found")
ELSE (GLM_FOUND)
	MESSAGE(FATAL_ERROR "Looking for GLM - not found")
ENDIF(GLM_FOUND)
INCLUDE_DIRECTORIES(${GLM_INCLUDE_DIRS})

# -------------------------------------------------------------
# Build & Export                     
# -------------------------------------------------------------
add_library(cgutils STATIC ${CGUTILS_SRCFILES})
TARGET_LINK_LIBRARIES(cgutils ${LIBS})
set (CGUTILS_LIBRARY cgutils PARENT_SCOPE) # export the lib up

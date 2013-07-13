cmake_minimum_required (VERSION 2.6)
INCLUDE(CMakeDependentOption)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ldl -std=c++11")

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
# FreeImage Dependency Tracking                         
# -------------------------------------------------------------
INCLUDE(${CGUTILS_CMAKE_DIR}/FindFreeImage.cmake)
IF(FREEIMAGE_FOUND)
	SET(HAVE_FREEIMAGE ${FREEIMAGE_FOUND} CACHE BOOL "Set to TRUE if FreeImage is found, FALSE otherwise")
	MESSAGE(STATUS "Looking for FreeImage - found")
	SET(LIBS ${LIBS} ${FREEIMAGE_LIBRARIES})
	INCLUDE_DIRECTORIES(${FREEIMAGE_INCLUDE_PATH})
ELSE(FREEIMAGE_FOUND)
	MESSAGE(FATAL_ERROR "Looking for FreeImage - not found")
ENDIF(FREEIMAGE_FOUND)

# -------------------------------------------------------------
# Boost Dependency Tracking                         
# -------------------------------------------------------------
FIND_PACKAGE( Boost COMPONENTS system program_options filesystem thread  REQUIRED )
IF (Boost_FOUND)
	MESSAGE(STATUS "Looking for Boost - found")
	SET(LIBS ${LIBS} ${Boost_LIBRARIES})
	INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
ELSE (Boost_FOUND)
	MESSAGE(FATAL_ERROR "Looking for Boost - not found")
ENDIF(Boost_FOUND)

# -------------------------------------------------------------
# Assimp Dependency Tracking                         
# -------------------------------------------------------------
INCLUDE( ${CGUTILS_CMAKE_DIR}/FindAssimp.cmake )
IF (ASSIMP_FOUND)
	MESSAGE(STATUS "Looking for Assimp - found")
	SET(LIBS ${LIBS} ${ASSIMP_LIBRARY})
	INCLUDE_DIRECTORIES(${ASSIMP_INCLUDE_DIR})
	set(ASSIMP_ENABLED true)
ELSE (ASSIMP_FOUND)
	MESSAGE(FATAL_ERROR "Looking for Assimp - not found")
ENDIF(ASSIMP_FOUND)

# -------------------------------------------------------------
# GLM Dependency Tracking                         
# -------------------------------------------------------------
INCLUDE( ${CGUTILS_CMAKE_DIR}/FindGLM.cmake )
IF (GLM_FOUND)
	MESSAGE(STATUS "Looking for GLM - found")
	INCLUDE_DIRECTORIES(${GLM_INCLUDE_DIRS})
ELSE (GLM_FOUND)
	MESSAGE(FATAL_ERROR "Looking for GLM - not found")
ENDIF(GLM_FOUND)

# -------------------------------------------------------------
# FbxSdk Dependency Tracking                         
# -------------------------------------------------------------
INCLUDE( ${CGUTILS_CMAKE_DIR}/FindFBXSDK.cmake )
IF (FBX_FOUND)
	MESSAGE(STATUS "Looking for FBXSDK - found")
	set(FBXSDK_ENABLED true)
	SET(LIBS ${LIBS} ${FBX_LIBRARY})
	INCLUDE_DIRECTORIES(${FBX_INCLUDE_DIR})
ELSE (FBX_FOUND)
	MESSAGE(STATUS "Looking for FBXSDK - not found")
ENDIF(FBX_FOUND)

# -------------------------------------------------------------
# SDL2 Dependency Tracking                     
# -------------------------------------------------------------
INCLUDE( ${CGUTILS_CMAKE_DIR}/FindSDL2.cmake )
IF (SDL2_FOUND)
	MESSAGE(STATUS "Looking for SDL2 - found")
	SET(LIBS ${LIBS} ${SDL2_LIBRARY})
	INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR})
ELSE (SDL2_FOUND)
	MESSAGE(STATUS "Looking for SDL2 - not found")
ENDIF(SDL2_FOUND)

# -------------------------------------------------------------
# OpenGL Dependency Tracking                     
# -------------------------------------------------------------
INCLUDE( ${CGUTILS_CMAKE_DIR}/FindOpenGL.cmake )
IF (OPENGL_FOUND)
	MESSAGE(STATUS "Looking for OpenGL - found")
	SET(LIBS ${LIBS} ${OPENGL_LIBRARIES})
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
ELSE (OPENGL_FOUND)
	MESSAGE(STATUS "Looking for OpenGL - not found")
ENDIF(OPENGL_FOUND)

# -------------------------------------------------------------
# GLEW Dependency Tracking                     
# -------------------------------------------------------------
IF (OPENGL_FOUND)
	INCLUDE( ${CGUTILS_CMAKE_DIR}/FindGLEW.cmake )
	IF (GLEW_FOUND)
		MESSAGE(STATUS "Looking for GLEW - found")
		SET(LIBS ${LIBS} ${GLEW_LIBRARY})
		INCLUDE_DIRECTORIES(${GLEW_INCLUDE_PATH})
	ELSE (GLEW_FOUND)
		MESSAGE(FATAL_ERROR "Looking for GLEW - not found")
	ENDIF(GLEW_FOUND)
ENDIF(OPENGL_FOUND)

# -------------------------------------------------------------
# Rocket Dependency Tracking                     
# -------------------------------------------------------------
INCLUDE( ${CGUTILS_CMAKE_DIR}/FindRocket.cmake )
IF (ROCKET_FOUND)
	MESSAGE(STATUS "Looking for Rocket - found")
	SET(LIBS ${LIBS} ${ROCKET_LIBRARY})
	INCLUDE_DIRECTORIES(${ROCKET_INCLUDE_DIR})
ELSE (ROCKET_FOUND)
	MESSAGE(STATUS "Looking for Rocket - not found")
ENDIF(ROCKET_FOUND)

# -------------------------------------------------------------
# CEGUI Dependency Tracking                     
# -------------------------------------------------------------
INCLUDE( ${CGUTILS_CMAKE_DIR}/FindCEGUI.cmake )
IF (CEGUI_FOUND)
	MESSAGE(STATUS "Looking for CEGUI - found")
	SET(LIBS ${LIBS} ${CEGUI_LIBRARY})
	INCLUDE_DIRECTORIES(${CEGUI_INCLUDE_DIRS})
ELSE (CEGUI_FOUND)
	MESSAGE(STATUS "Looking for CEGUI - not found")
ENDIF(CEGUI_FOUND)


# -------------------------------------------------------------
# Source Tree Variables                       
# -------------------------------------------------------------
set(CGUTILS_SRCFILES "")
add_subdirectory(${CGUTILS_SRCS_DIR})
include_directories("${CGUTILS_INCLUDE_DIR}")

# -------------------------------------------------------------
# Build Configuration                  
# -------------------------------------------------------------
option(MESH_ALLOCATION_STRATEGY_HARDWARE "Allocate mesh resources in hardware buffers" ON)
option(RENDERSYSTEM_ENABLED "Include rendersystem framework" ON)
IF (OPENGL_FOUND)
	CMAKE_DEPENDENT_OPTION(OPENGL_ENABLED "Use opengl" ON "RENDERSYSTEM_ENABLED" OFF)
ENDIF(OPENGL_FOUND)
CONFIGURE_FILE( ${CGUTILS_INCLUDE_DIR}/buildsettings.h.in ${CGUTILS_INCLUDE_DIR}/buildsettings.h )

# -------------------------------------------------------------
# Build & Export                     
# -------------------------------------------------------------
add_library(cgutils STATIC ${CGUTILS_SRCFILES})
TARGET_LINK_LIBRARIES(cgutils ${LIBS})
set (CGUTILS_LIBRARY cgutils PARENT_SCOPE) # export the lib up

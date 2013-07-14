# - Locate CEGUI library
# This module defines
#  CEGUI_LIBRARY, the library to link against
#  CEGUI_FOUND, if false, do not try to link to CEGUI
#  CEGUI_INCLUDE_DIRS, where to find headers.

FIND_PATH(CEGUI_INCLUDE_DIRS
  Scheme.h
  PATHS
  $ENV{CEGUI_DIR}/include
  /usr/local/include
  /usr/include
  /sw/include
  /opt/local/include
  /opt/csw/include
  /opt/include
  PATH_SUFFIXES CEGUI
)

FIND_LIBRARY(CEGUI_BASE_LIBRARY
  NAMES CEGUIBase CEGUIBase-0
  PATHS
  $ENV{CEGUI_DIR}/lib
  /usr/local/lib
  /usr/lib
  /usr/local/X11R6/lib
  /usr/X11R6/lib
  /sw/lib
  /opt/local/lib
  /opt/csw/lib
  /opt/lib
  /usr/freeware/lib64
  PATH_SUFFIXES
)

FIND_LIBRARY(CEGUI_GL_LIBRARY
  NAMES CEGUIOpenGLRenderer CEGUIOpenGLRenderer-0
  PATHS
  $ENV{CEGUI_DIR}/lib
  /usr/local/lib
  /usr/lib
  /usr/local/X11R6/lib
  /usr/X11R6/lib
  /sw/lib
  /opt/local/lib
  /opt/csw/lib
  /opt/lib
  /usr/freeware/lib64
  PATH_SUFFIXES cegui-0.8 
)

if(CEGUI_BASE_LIBRARY AND CEGUI_GL_LIBRARY)
  SET(CEGUI_LIBRARY ${CEGUI_GL_LIBRARY} ${CEGUI_BASE_LIBRARY})
ENDIF(CEGUI_BASE_LIBRARY AND CEGUI_GL_LIBRARY)

IF(CEGUI_LIBRARY AND CEGUI_INCLUDE_DIRS)
  SET(CEGUI_FOUND "YES")
  SET(CEGUI_INCLUDE_DIRS "${CEGUI_INCLUDE_DIRS}/CEGUI")
  IF(NOT CEGUI_FIND_QUIETLY)
    MESSAGE(STATUS "Found CEGUI: ${CEGUI_LIBRARY}")
  ENDIF(NOT CEGUI_FIND_QUIETLY)
ELSE(CEGUI_LIBRARY AND CEGUI_INCLUDE_DIRS)
  IF(NOT CEGUI_FIND_QUIETLY)
    MESSAGE(STATUS "Warning: Unable to find CEGUI!")
  ENDIF(NOT CEGUI_FIND_QUIETLY)
ENDIF(CEGUI_LIBRARY AND CEGUI_INCLUDE_DIRS)

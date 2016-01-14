cmake_minimum_required(VERSION 2.8)
#Déclaration du projet
cmake_policy(SET CMP0004 OLD)
project(MyProject)
add_executable(MyProject main.c)



#Déclaration de l'exécutable

find_package(SDL2 REQUIRED)
if (SDL2_FOUND)
  include_directories(${SDL2_INCLUDE_DIR})
  target_link_libraries (MyProject ${SDL2_LIBRARIES})
endif (SDL2_FOUND)

#find_package(OpenGL REQUIRED)
#if (OpenGL_FOUND)
#  include_directories(${OPENGL_gl_INCLUDE_DIR})
#  target_link_libraries (MyProject ${OPENGL_gl_LIBRARY})
#endif (OpenGL_FOUND)
target_link_libraries (MyProject "/usr/lib/nvidia-352/libGL.so")

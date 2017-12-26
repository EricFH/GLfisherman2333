cmake_minimum_required(VERSION 3.9)
project(happyfisher)

set(CMAKE_CXX_STANDARD 11)

find_library(OPENGL opengl)
#find_library(GML gml)
# 添加头文件
set(GLEW_H /usr/local/Cellar/glew/2.1.0/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.2.1/include/GLFW)
set(ASSIMP_H /usr/local/Cellar/assimp/4.0.1/include/assimp)
#set(GLM_H /usr/local/Cellar/glm/0.9.8.5/include/glm)

include_directories(${GLEW_H} ${GLFW_H} ${ASSIMP_H})

# 添加目标链接
set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.dylib)
set(ASSIMP_LINK /usr/local/Cellar/assimp/4.0.1/lib/libassimp.4.dylib)
#set(GLM_LINK /usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK} ${ASSIMP_LINK})

# 执行编译命令
set(SOURCE_FILES main.cpp obj/camera.h obj/camera.cpp obj/shader.h obj/model.h obj/mesh.h obj/stb_image.cpp obj/mesh.cpp obj/common.h obj/model.cpp obj/shader.cpp fish.cpp fish.h fishmanager.cpp fishmanager.h manager.cpp manager.h obj/collision.h obj/collision.cpp)
add_executable(happyfisher ${SOURCE_FILES})
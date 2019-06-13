cmake_minimum_required(VERSION 3.6)
project(glew_stuff)

set(SRC_DIR src/)
#file(GLOB ${SRC_DIR}
#        "*.cpp"
#        "*.c"
#        "*.h")
file(GLOB_RECURSE SOIL2_SRC src/SOIL2/*.c src/SOIL2/*.h)
set(SOURCES src/app/Application.cpp src/app/Application.h src/app/utils/utils.cpp
        src/app/utils/utils.h src/app/script_engine/IEngine.h
        src/app/script_engine/LuaScriptEngine.cpp src/app/script_engine/LuaScriptEngine.h
        src/app/character/ICharacter.h src/app/character/Character.cpp
        src/app/character/Character.h src/app/character/DirectionalAsset.cpp
        src/app/character/IMovable.h src/app/character/IMovable.cpp)
set(LIB_DIR lib/)
set(CMAKE_CXX_STANDARD 11)
add_definitions(-DGLEW_STATIC)

set(CMAKE_VERBOSE_MAKEFILE 1)
add_executable(glew_stuff main.cpp ${SOURCES} ${SOIL2_SRC})
link_directories(${LIB_DIR})


# lua
find_package(lua51 REQUIRED)
include_directories(${LUA_INCLUDE_DIRS})
link_libraries(${LUA_LIBRARY_DIRS})

# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

#SOIL2
#set(SOIL2_DIR "${LIB_DIR}/SOIL2")
#include_directories(lib/SOIL2/incs)
#add_library()
#add_subdirectory("${SOIL2_DIR}")
#add_custom_target(
#        SOIL2
#        COMMAND make
#        WORKING_DIRECTORY ${SOIL2_DIR}
#)
#target_link_libraries(glew_stuff SOIL2 ${SOIL2_DIR}/libSOIL2.a)
#target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

if (APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    target_link_libraries(glew_stuff "-framework OpenGL")
    SET(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif (APPLE)

target_link_libraries(
        glew_stuff
        glfw
        ${SOIL2_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${EXTRA_LIBS}
        ${LUA_LIBRARIES}
        ${SOIL2_LIBRARIES}
)
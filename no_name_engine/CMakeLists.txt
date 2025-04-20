cmake_minimum_required(VERSION 3.16...3.24)
project(no_name_engine)

set(CMAKE_CXX_FLAGS "" CACHE STRING "" FORCE)

set(FILAMENT_WARNINGS "" CACHE STRING "" FORCE)
set(FILAMENT_FATAL_WARNINGS "" CACHE STRING "" FORCE)
set(SPIRV_WERROR "" CACHE STRING "" FORCE)

# Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detect number of CPU cores
include(ProcessorCount)
ProcessorCount(NUM_THREADS)

if (NOT NUM_THREADS EQUAL 0)
    message(STATUS "🛠️  Parallel build will use ${NUM_THREADS} threads.")
else ()
    message(WARNING "Could not detect number of CPU cores. Defaulting to 1 thread.")
    set(NUM_THREADS 1)
endif ()
set(NUM_THREADS ${NUM_THREADS} CACHE INTERNAL "Number of CPU threads detected")

# Packages
find_package(glfw3 3.2 REQUIRED)
find_package(GLEW REQUIRED)

# Paths
set(BULLET_PATH third_party/bullet)
set(SPDLOG_PATH third_party/spdlog)
set(FILAMENT_PATH third_party/filament)

# Bullet build rules
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build Bullet as static library")
set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "Disable Bullet2 demos")
set(BUILD_CPU_DEMOS OFF CACHE BOOL "Disable CPU demos")
set(BUILD_OPENGL3_DEMOS OFF CACHE BOOL "Disable OpenGL demos")
set(BUILD_UNIT_TESTS OFF CACHE BOOL "Disable Unit Tests")
set(BUILD_EXTRAS OFF CACHE BOOL "Disable Extras")
set(INSTALL_LIBS ON CACHE BOOL "Install Bullet libraries")

# Submodules
add_subdirectory(${BULLET_PATH})
add_subdirectory(${SPDLOG_PATH})
add_subdirectory(${FILAMENT_PATH})

file(GLOB_RECURSE EVENT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/event/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/event/*.cpp
)

file(GLOB_RECURSE SCENE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scene/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scene/*.cpp
)

file(GLOB_RECURSE RENDER_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/render/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/render/*.cpp
)

file(GLOB_RECURSE PHYSICS_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/physics/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/physics/*.cpp
)

file(GLOB_RECURSE ENGINE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/*.cpp
)

# Main engine library
add_library(no_name_engine SHARED
        ${EVENT_SOURCES}
        ${SCENE_SOURCES}
        ${PHYSICS_SOURCES}
        ${RENDER_SOURCES}
        ${ENGINE_SOURCES}
        no_name_engine.h
)

# Includes
target_include_directories(no_name_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${BULLET_PATH}/src)

# Linking
target_link_libraries(no_name_engine PUBLIC
        BulletDynamics
        BulletCollision
        LinearMath
        spdlog::spdlog
        glfw
        GLEW::GLEW
        filament
        "-framework OpenGL"
)

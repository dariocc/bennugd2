project(mod_tmx)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../../bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin/")

set(CMAKE_MODULE_PATH ../../cmake/Modules)

find_package(SDL2 REQUIRED)
find_package(SDL_GPU REQUIRED)

add_definitions(-D__LIBBGFGX $ENV{EXTRA_CFLAGS})

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS} ../../core/include ../../core/bgdrtm ../libbggfx ../libmod_gfx ../../modules/libmod_tmx ${SDL_GPU_INCLUDE_DIR})

file(GLOB SOURCES_LIBMOD_TMX
     "../../modules/libmod_tmx/*.c"
     )

find_library(TMX_LIB NAMES tmx PATHS /usr/local/lib64)
find_path(TMX_INCLUDE_DIRS tmx.h PATHS /usr/local/include)
include_directories(${TMX_INCLUDE_DIRS})

add_library(mod_tmx SHARED ${SOURCES_LIBMOD_TMX})
target_link_libraries(bggfx ${SDL2_LIBRARIES} ${SDL_GPU_LIBRARY} mod_tmx ${TMX_LIB} -L../../bin -lbgdrtm)
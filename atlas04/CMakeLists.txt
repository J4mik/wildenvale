cmake_minimum_required(VERSION 3.15...3.31)
project(WarOfDungeons
VERSION 1.0
DESCRIPTION "Pixel art platformer"
LANGUAGES C CXX)

set(CMAKE_CPP_COMPILER g++)
set(CMAKE_MAKE_PROGRAM ninja)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(ATLAS_GEN_NAME "gen04")

add_compile_options(-Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=maybe-uninitialized -Warray-bounds -g -lefence)

set(CMAKE_CXX_FLAGS) # -mwindows)

# -Iinclude
include_directories(${CMAKE_SOURCE_DIR}/include)
# -Llib
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(WarOfDungeons
	src/defs.h src/structs.h src/atlas.c src/atlas.h src/atlasGen.c src/atlasGen.h 
	src/cJSON.c src/cJSON.h src/common.h src/demo.c src/demo.h src/draw.c src/draw.h 
	src/init.c src/init.h src/input.c src/input.h src/main.c src/main.h src/util.c 
	src/util.h
)

set(SDL3_LIBRARIES mingw32 SDL3 SDL3_image SDL3_mixer SDL3_ttf)

target_link_libraries(WarOfDungeons PUBLIC ${SDL3_LIBRARIES})
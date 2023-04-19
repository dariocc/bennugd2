#include <stdlib.h>
#include <string.h>
#include <tmx.h>

#include "bgddl.h"

#include "files.h"
#include "xctype.h"
#include "xstrings.h"
#include "g_bitmap.h"
#include "m_map.h"
#include "g_grlib.h"

#include "dlvaracc.h"

#include "libmod_tmx.h"

typedef struct _tex {
    int64_t graph;
} TMX_TEX;


static int64_t libmod_tmx_load_map(INSTANCE * my, int64_t * params) {
    const char *filename;
    if ( ! (filename = string_get(params[0])) ) {
        return 0;
    }
    tmx_map *map = tmx_load(filename);
    if (!map) {
        tmx_perror("Cannot load map");
        return -1;
    }
    return (int64_t)map;
}

static uint32_t libmod_tmx_get_map_width(INSTANCE * my, int64_t * params) {
    tmx_map * map = (tmx_map *)params[0];
    return map->width;
}

static uint32_t libmod_tmx_get_map_height(INSTANCE * my, int64_t * params) {
    tmx_map * map = (tmx_map *)params[0];
    return map->height;
}

static uint32_t libmod_tmx_get_map_tile_width(INSTANCE * my, int64_t * params) {
    tmx_map * map = (tmx_map *)params[0];
    return map->tile_width;
}

static uint32_t libmod_tmx_get_map_tile_height(INSTANCE * my, int64_t * params) {
    tmx_map * map = (tmx_map *)params[0];
    return map->tile_height;
}

static int64_t libmod_tmx_get_map_tile_image(INSTANCE * my, int64_t * params) {
    tmx_map * map = (tmx_map *)params[0];
    uint32_t gid = params[1];
    if (map->tiles[gid]) {
        return ((TMX_TEX *)map->tiles[gid]->image)->graph;
    }
    return 0;
}

static int64_t libmod_tmx_unload_map(INSTANCE * my, int64_t * params) {
    tmx_map * map = (tmx_map *)params[0];
    tmx_map_free(map);
}

static void* tex_load(const char *path) {
    TMX_TEX * tex = malloc(sizeof(TMX_TEX));
    tex->graph = gr_load_img(path);
    return tex;
}

static void* tex_free(void * handler) {
    TMX_TEX * tex = (TMX_TEX *)handler;
    return (void *) grlib_unload_map(0, tex->graph);
}

void __bgdexport( libmod_tmx, module_initialize )() {
    tmx_img_load_func = tex_load;
}

void __bgdexport( libmod_tmx, module_finalize )() {
}

#include "libmod_tmx_exports.h"

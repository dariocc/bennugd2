#include <stdio.h> // TODO: Remove me
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

static const int TMX_MAX_MAP_ID = 1;
static tmx_last_map_id = 0;
static tmx_map **tmx_maps; // 1-based array (first element is always ignored)

static uint64_t libmod_tmx_load_map(INSTANCE * my, int64_t * params) {
    const char *filename;
    tmx_map **result = (tmx_map **) (params[1]);
    
    if ( ! (filename = string_get(params[0])) ) {
        return 0;
    }

    tmx_map *map = tmx_load(filename);
    if (!map) {
        tmx_perror("Cannot load map");
        return 0;
    }

    // TODO: Only if debug
    printf("Size of map: %dx%d\n", map->width, map->height);
    printf("sizeof(map.orient): %d\n", sizeof map->orient);
    printf("sizeof(map.width): %d\n", sizeof map->width);
    printf("sizeof(map.height): %d\n", sizeof map->height);
    printf("sizeof(map.tile_width): %d\n", sizeof map->tile_width);
    printf("sizeof(map.tile_height): %d\n", sizeof map->tile_height);
    printf("sizeof(map.stagger_index): %d\n", sizeof map->stagger_index);
    printf("sizeof(map.stagger_axis): %d\n", sizeof map->stagger_axis);
    printf("sizeof(map.hexidelength): %d\n", sizeof map->hexsidelength);
    printf("sizeof(map.backgroundcolor): %d\n", sizeof map->backgroundcolor);
    printf("sizeof(map.renderorder): %d\n", sizeof map->renderorder);
    printf("sizeof(map.prperties): %d\n", sizeof map->properties);
    printf("sizeof(map.ts_head): %d\n", sizeof map->ts_head);
    printf("sizeof(map.ly_head): %d\n", sizeof map->ly_head);
    printf("sizeof(map.tilecount): %d\n", sizeof map->tilecount);
    printf("sizeof(map.tiles): %d\n", sizeof map->tiles);
    printf("sizeof(map.user_data): %d\n", sizeof map->user_data);


    tmx_last_map_id++;
    tmx_maps[tmx_last_map_id] = map;

    *result = map;

    return tmx_last_map_id;
}

static int64_t libmod_tmx_unload_map(INSTANCE * my, int64_t * params) {
    int64_t tilemap_id = params[0];
    tmx_map_free(tmx_maps[tilemap_id]);
}

static void* tex_load(const char *path) {
    int64_t *handler = malloc(sizeof(handler));
    *handler = gr_load_img(path);
    return handler;
}

static void* tex_free(void * handler) {
    return (void *) grlib_unload_map(0, (int64_t *)handler);
}

void __bgdexport( libmod_tmx, module_initialize )() {
    tmx_img_load_func = tex_load;
    tmx_maps = malloc(sizeof *tmx_maps * TMX_MAX_MAP_ID);
}

void __bgdexport( libmod_tmx, module_finalize )() {
}

#include "libmod_tmx_exports.h"

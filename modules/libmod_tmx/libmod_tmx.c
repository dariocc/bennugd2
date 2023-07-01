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

typedef struct tmx_tex_t {
    int64_t graph;
} tmx_tex_t;

typedef struct tmx_layer_l_t {
    int32_t *guids;
} tmx_layer_l_t;

typedef struct tmx_layer_t {
    int32_t id;
    int32_t visible;
    int32_t offsetx;
    int32_t offsety;
    int32_t type;
    void *content;
    struct tmx_layer_t *next;
} tmx_layer_t;

typedef struct tmx_tilemap_t {
    int32_t id;
    uint32_t orient;
    uint32_t width;
    uint32_t height;
    uint32_t tile_width;
    uint32_t tile_height;
    uint32_t tilecount;
    int32_t stagger_index;
    int32_t stager_axis;
    uint32_t backgroundcolor;
    uint32_t renderorder;

    void *first_Layer;
} tmx_tilemap_t;

static int64_t tmx_id_count = 0;
static tmx_map * tmx_maps[9999];

static uint64_t libmod_tmx_load_map(INSTANCE * my, int64_t * params) {
    const char *filename;
    if ( ! (filename = string_get(params[0])) ) {
        return 0;
    }

    tmx_map *map = tmx_load(filename);
    if (!map) {
        tmx_perror("Cannot load map");
        return 0;
    }

    tmx_id_count++;
    tmx_maps[tmx_id_count] = map;

    tmx_tilemap_t *tilemap_t=(tmx_tilemap_t *)( intptr_t )(params[1]);
    tilemap_t->id=tmx_id_count;
    tilemap_t->orient = map->orient;
    tilemap_t->width = map->width;
    tilemap_t->height = map->height;
    tilemap_t->tile_width = map->tile_width;
    tilemap_t->tile_height = map->tile_height;
    tilemap_t->tilecount = map->tilecount;
    tilemap_t->stagger_index = map->stagger_index;
    tilemap_t->stager_axis = map->stagger_axis;
    tilemap_t->backgroundcolor = map->backgroundcolor;
    tilemap_t->renderorder = map->renderorder;

    return tmx_id_count;
}

static void extract_layer(tmx_layer_t *layer_t, tmx_layer * layer) {
    layer_t->id = layer->id;
    layer_t->offsetx = layer->offsetx;
    layer_t->offsety = layer->offsety;
    layer_t->type = layer->type;
    layer_t->visible = layer->visible;
    layer_t->next = (void *)layer->next;
    switch(layer_t->type) {
        case L_LAYER:
            layer_t->content = layer->content.gids;
            break;
        case L_IMAGE:
            layer_t->content = layer->content.image;
            break;
        case L_OBJGR:
            layer_t->content = layer->content.objgr;
            break;
        case L_GROUP:
            layer_t->content = layer->content.group_head;
            break;
    }
}

static void libmod_tmx_first_layer(INSTANCE * my, int64_t * params) {
    int64_t tilemap_id = params[0];
    tmx_layer_t *layer_t = (tmx_layer_t *)( intptr_t )(params[1]);
    extract_layer(layer_t, tmx_maps[tilemap_id]->ly_head);
}

static void libmod_tmx_next_layer(INSTANCE *my, int64_t * params) {
    tmx_layer_t *layer_t = (tmx_layer_t *)( intptr_t )(params[0]);
    tmx_layer * next_layer = (tmx_layer *) layer_t->next;
    extract_layer(layer_t, next_layer);
}

static void libmod_tmx_as_l_layer(INSTANCE * my, int64_t * params) {
    tmx_layer_t *layer_t = (tmx_layer_t *)( intptr_t )(params[0]);
    tmx_layer_l_t *layer_l_t = (tmx_layer_l_t *)( intptr_t )(params[1]);
    layer_l_t->guids = layer_t->content;
}

static int64_t libmod_tmx_unload_map(INSTANCE * my, int64_t * params) {
    int64_t tilemap_id = params[0];
    tmx_map_free(tmx_maps[tilemap_id]);
}

static void* tex_load(const char *path) {
    tmx_tex_t * tex = malloc(sizeof(tmx_tex_t));
    tex->graph = gr_load_img(path);
    return tex;
}

static void* tex_free(void * handler) {
    tmx_tex_t * tex = (tmx_tex_t *)handler;
    return (void *) grlib_unload_map(0, tex->graph);
}

void __bgdexport( libmod_tmx, module_initialize )() {
    tmx_img_load_func = tex_load;
}

void __bgdexport( libmod_tmx, module_finalize )() {
}

#include "libmod_tmx_exports.h"

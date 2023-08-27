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
    if ( ! (filename = string_get(params[0])) ) {
        return 0;
    }

    tmx_map *map = tmx_load(filename);
    if (!map) {
        tmx_perror("Cannot load map");
        return 0;
    }

    tmx_last_map_id++;
    tmx_maps[tmx_last_map_id] = map;

    return tmx_last_map_id;
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
    tmx_maps = malloc(sizeof *tmx_maps * TMX_MAX_MAP_ID);
}

void __bgdexport( libmod_tmx, module_finalize )() {
}

#include "libmod_tmx_exports.h"

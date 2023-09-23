import "libmod_gfx";
import "libmod_input";
import "libmod_tmx";
import "libmod_misc";

#include "../common/common.h"

TYPE TMX_TILE_T
  UINT32 id;
  INT POINTER tileset; // TODO: Implement me
  UINT32 ul_x;
  UINT32 ul_y;
  INT POINTER image; // TODO: Implement me
END

TYPE TMX_L_LAYER_T
  UINT32 POINTER guids;
END

TYPE TMX_LAYER_T
  INT32 _reserved; // Still trying to figure out why this is needed
  INT32 id=0;
  
  CHAR POINTER name;
  DOUBLE opacity=0;
  INT32 visible=0;
  INT32 offsetx=0;
  INT32 offsety=0;

  INT32 type=0;
  INT POINTER layer_content;

  INT POINTER user_data;
  INT POINTER properties; // TODO: Implement me
  TMX_LAYER_T POINTER next;
END

TYPE TMX_MAP_T
  UINT32 orient=0;

  UINT32 width=0;
  UINT32 height=0;
  UINT32 tile_width=0;
  UINT32 tile_height=0;

  UINT32 stagger_index=0;
  UINT32 stagger_axis=0;
  UINT32 hexsidelength=0;

  UINT32 backgroundcolor=0;
  UINT32 renderorder=0;

  INT POINTER PROPERTIES;
  INT POINTER TS_HEAD;          // TODO: Placeholder
  TMX_LAYER_T POINTER LY_HEAD;

  UINT32 tilecount=0;
  TMX_TILE_T POINTER POINTER tiles;

  INT POINTER USER_DATA;
END

// ---

process main()
private
  int tilemap_id;
  tmx_map_t *tilemap;
begin

#include "../common/init_video.h"

  tilemap_id = tmx_load("map.tmx", &tilemap);

#ifdef __DEBUG__
  dump_tmx_map_t(tilemap);
#endif

  write(0,160,190,ALIGN_CENTER,"(press F for switch fullscreen/window)");
  
  render_map(tilemap);

  while( !key(_ESC) )
    if ( key(_f) )
      screen.fullscreen ^= 1;
      set_mode(SCRW,SCRH);
      while(key(_f)) frame; end
    end
    frame;
  end

  tmx_unload(tilemap_id);
end

process render_tile(int tile_graph, int tile_x, int tile_y, int tile_w, int tile_h)
begin
  loop
    frame;
  end
end

/*
process render_l_layer(tmx_tilemap_t* tilemap, tmx_l_layer_t* l_layer)
private
  int row, col;
  int gid;
begin
  for (row=0; row < tilemap.height; row++)
    for (col=0; col < tilemap.width; col++)
      gid=itoa(l_layer.guids[row * tilemap.width + col]); // & TMX_FLIP_BITS_REMOVAL;
      say("gid: " + gid);
      say(tilemap.tiles);
      say(tilemap.tiles[1]);
      
      if (gid != 0 && tilemap.tiles[gid] != 0)
        say("tilemap.tiles[gid].id " + tilemap.tiles[gid].id);
        say("tilemap.tiles[gid].ul_x " + tilemap.tiles[gid].ul_x);
        say("tilemap.tiles[gid].ul_y " + tilemap.tiles[gid].ul_y);
        say("tilemap.tiles[gid].tileset " + tilemap.tiles[gid].tileset);
        say("tilemap.tiles[gid].image " + tilemap.tiles[gid].image);
        
        if (tilemap.tiles[gid].image)
          // Image from resource
        else
          // Image from tileset
        end
        
        // Use gid to get the tile in the tile structure of the tilemap and render it
        render_tile(tile_graph, tile_x, tile_y, tile_w, tile_h);
      end
    end
  end
end
*/

process render_map(tmx_map_t* tilemap)
private
  tmx_layer_t *layer;
begin
  layer=tilemap.ly_head;
  loop

#ifdef __DEBUG__
    dump_layer_t(layer);
#endif

    switch (layer.type)
      case TMX_L_LAYER:
        // tmx_as_l_layer(&layer, &l_layer);
        // render_l_layer(tilemap, &l_layer);
      end
      case TMX_L_OBJGR:
        // Implement me
      end
      case TMX_L_IMAGE:
        // Implement me
      end
      case TMX_L_GROUP:
        // Implement me
      end
      default:
        // Implement me
        break;
      end
    end
    if (layer.next==0) 
      break; 
    end
    layer=layer.next;
  end
end

function dump_tmx_map_t(tmx_map_t *map)
begin
  say("--- 11-tmx.prg::map ----");
  say("map.orient: " + itoa(map.orient));
  say("map.width: " + itoa(map.width));
  say("map.height: " + itoa(map.height));
  say("map.tile_width: " + itoa(map.tile_width));
  say("map.tile_height: " + itoa(map.tile_height));
  say("map.stagger_index: " + itoa(map.stagger_index));
  say("map.stagger_axis: " + itoa(map.stagger_axis));
  say("map.hexsidelenght: " + itoa(map.hexsidelength));
  say("map.backgroundcolor: " + itoa(map.backgroundcolor));
  say("map.renderorder: " + itoa(map.renderorder));
  say("map.tilecount: " + itoa(map.tilecount));
end

function dump_layer_t(tmx_layer_t *layer)
begin
  say("--- 11-tmx.prg::layer ----");
  say("layer (address): " + itoa(layer));
  say("sizeof(layer.id): " + itoa(sizeof(layer.id)));
  say("sizeof(layer.name): " + itoa(sizeof(layer.name)));
  say("sizeof(layer.opacity): " + ftoa(sizeof(layer.opacity)));
  say("sizeof(layer.visible): " + itoa(sizeof(layer.visible)));
  say("sizeof(layer.offsetx): " + itoa(sizeof(layer.offsetx)));
  say("sizeof(layer.offsety): " + itoa(sizeof(layer.offsety)));
  say("sizeof(layer.type): " + itoa(sizeof(layer.type)));
  say("layer.id: " + itoa(layer.id));
  say("layer.name: " + "<char pointer>");
  say("layer.opacity: " + ftoa(layer.opacity));
  say("layer.visible: " + itoa(layer.visible == 0));
  say("layer.offsetx: " + itoa(layer.offsetx));
  say("layer.offsety: " + itoa(layer.offsety));
  say("layer.type: " + itoa(layer.type));
  say("layer.next: " + itoa(layer.next));
end
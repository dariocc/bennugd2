import "libmod_gfx";
import "libmod_input";
import "libmod_tmx";
import "libmod_misc";

#include "../common/common.h"

process main()
private
  tmx_tilemap_t tilemap;
  int map_width;
begin

#include "../common/init_video.h"

  say(tmx_load("map.tmx", &tilemap));
  say("tilemap orient: " + itoa(tilemap.orient));
  say("tilemap width: " + itoa(tilemap.width));
  say("tilemap height: " + itoa(tilemap.height));
  say("tilemap tile_width: " + itoa(tilemap.tile_width));
  say("tilemap tile_height: " + itoa(tilemap.tile_height));
  say("tilemap tile_count: " + itoa(tilemap.tilecount));
  say("tilemap stagger_index: " + itoa(tilemap.stagger_index));
  say("tilemap stagger_axis: " + itoa(tilemap.stagger_axis));
  say("tilemap backgroundcolor: " + itoa(tilemap.backgroundcolor));
  say("tilemap renderorder: " + itoa(tilemap.renderorder));

  write(0,160,190,ALIGN_CENTER,"(press F for switch fullscreen/window)");

  while( !key(_ESC) )
    if ( key(_f) )
      screen.fullscreen ^= 1;
      set_mode(SCRW,SCRH);
      while(key(_f)) frame; end
    end
    frame;
  end

  tmx_unload(tilemap.id);
end

/*
process render_tile(int tile_graph, int tile_x, int tile_y, int tile_w, int tile_h)
begin
  loop
    frame;
  end
end

process render_l_layer(tmx_tilemap_t tilemap, tmx_l_layer pointer layer)
private
  int row, col;
begin
  for (row=0; row < map.height; row++)
    for (col=0; col < map.width; col++)
      // render_tile(tile_graph, tile_x, tile_y, tile_w, tile_h);
    end
  end
end

process render_map(tmx_tilemap_t tilemap)
private
  tmx_l_layer_t l_layer;
  tmx_layer next_layer;
begin
  tmx_first_layer(tilemap.id, &next_layer);
  repeat
    switch (next_layer.type)
      case TMX_L_LAYER:
        tmx_l_layer(&next_layer, &l_layer);
      end
      case TMX_L_OBJGRP:
        // Implement me
      end
      case TMX_L_IMAGE:
        // Implement me
      end
      case TMX_GROUP:
        // Implement me
      end
      default:
        // Implement me
        break;
      end
    end
    tmx_next_layer(&next_layer);
  until(next_layer.next==0)
end
*/
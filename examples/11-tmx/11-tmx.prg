import "libmod_gfx";
import "libmod_input";
import "libmod_tmx";
import "libmod_misc";

#include "../common/common.h"

process main()
private
  int tilemap_id;
  tmx_map_t *tilemap;
begin

#include "../common/init_video.h"

  tilemap_id = tmx_load("map.tmx", tilemap);
  say("tilemap id: " + itoa(tilemap_id));
  say("tilemap orient: " + itoa(tilemap.orient));
  say("tilemap width: " + itoa(tilemap.width));
  say("tilemap height: " + itoa(tilemap.height));
  say("tilemap tile_width: " + itoa(tilemap.tile_width));
  say("tilemap tile_height: " + itoa(tilemap.tile_height));
  say("tilemap tilecount: " + itoa(tilemap.tilecount));
  say("tilemap stagger_index: " + itoa(tilemap.stagger_index));
  say("tilemap stagger_axis: " + itoa(tilemap.stagger_axis));
  say("tilemap backgroundcolor: " + itoa(tilemap.backgroundcolor));
  say("tilemap renderorder: " + itoa(tilemap.renderorder));

  write(0,160,190,ALIGN_CENTER,"(press F for switch fullscreen/window)");
  
  //render_map(&tilemap);

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
  tmx_layer_t layer;
begin
  layer=*tilemap.ly_head;
  loop
    say("layer.id: " + itoa(layer.id));
    say("layer.visible: " + itoa(layer.visible));
    say("layer.offsetx: " + itoa(layer.offsetx));
    say("layer.offsety: " + itoa(layer.offsety));
    say("layer.type: " + itoa(layer.type));
    /*
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
    layer=*layer.next;
    */
  end
end
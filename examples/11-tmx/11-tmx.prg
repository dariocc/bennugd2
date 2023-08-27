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

  tmx_load("map.tmx", &tilemap);
  say("tilemap id: " + itoa(tilemap.id));
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
  
  render_map(&tilemap);

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

process render_tile(int tile_graph, int tile_x, int tile_y, int tile_w, int tile_h)
begin
  loop
    frame;
  end
end

process render_l_layer(tmx_tilemap_t* tilemap, tmx_l_layer_t* l_layer)
private
  int row, col;
  int gid;
begin
  for (row=0; row < tilemap.height; row++)
    for (col=0; col < tilemap.width; col++)
      gid=itoa(l_layer.guids[row * tilemap.width + col]); // & TMX_FLIP_BITS_REMOVAL;
      
      if (gid != 0 && tilemap.tiles[gid] != 0)
        say("gid: " + gid);
        say("tilemap[gid].id " + tilemap.tiles[gid].id);
        say("tilemap[gid].tileset " + tilemap.tiles[gid].tileset);
        say("tilemap[gid].image " + tilemap.tiles[gid].image);
        say("tilemap[gid].ul_x " + tilemap.tiles[gid].ul_x);
        say("tilemap[gid].ul_y " + tilemap.tiles[gid].ul_y);
        
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

process render_map(tmx_tilemap_t* tilemap)
private
  tmx_l_layer_t l_layer;
  tmx_layer_t next_layer;
begin
  tmx_first_layer(tilemap.id, &next_layer);
  loop
    say("layer.id: " + itoa(next_layer.id));
    say("layer.visible: " + itoa(next_layer.visible));
    say("layer.offsetx: " + itoa(next_layer.offsetx));
    say("layer.offsety: " + itoa(next_layer.offsety));
    say("layer.type: " + itoa(next_layer.type));
    switch (next_layer.type)
      case TMX_L_LAYER:
        tmx_as_l_layer(&next_layer, &l_layer);
        //render_l_layer(tilemap, &l_layer);
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
    if (next_layer.next==0) 
      break; 
    end
    tmx_next_layer(&next_layer);
  end
end
import "libmod_gfx";
import "libmod_input";
import "libmod_tmx";

#include "../common/common.h"

process main()
private
  int map;
  int map_width;
begin

#include "../common/init_video.h"

  map = tmx_load("map.tmx");

  write(0,160,190,ALIGN_CENTER,"(press F for switch fullscreen/window)");

  while( !key(_ESC) )
    if ( key(_f) )
      screen.fullscreen ^= 1;
      set_mode(SCRW,SCRH);
      while(key(_f)) frame; end
    end
    frame;
  end
end

process render_layer(int map, int layer)
private
  int map_width;
  int map_height;
  int col, row;
  int tile_graph;
  int tile_x;
  int tile_y;
  int tile_w;
  int tile_h;
begin
  map_width = tmx_get_map_width(map);
  map_height = tmx_get_map_height(map);

  for (row=0; row < map_height; row++)
    for (col=0; col < map_width; col++)
      render_tile(tile_graph, tile_x, tile_y, tile_w, tile_h);
    end
  end
end

process render_tile(int tile_graph, int tile_x, int tile_y, int tile_w, int tile_h)
begin
  loop
    frame;
  end
end
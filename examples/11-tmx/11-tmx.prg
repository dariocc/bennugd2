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
    map_width = tmx_get_map_width(map);

    write_var(0,160,10,ALIGN_CENTER,map_width);
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
begin

    for (row=0; row < map_height; row++)
        for (col=0; col < map_width; col++)
            gid = get_map_layer_gid(row * map_width + col);
            if (gid != 0)
                render_tile(image, x, y, w, h);
            end
        end
    end
end

process render_tile(int image, int x, int y, int w, int h)
begin
    loop
        frame;
    end
end
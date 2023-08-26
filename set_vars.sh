LD_LIBRARY_PATH=~/Projects/bennugd2/build/build-linux-gnu/bin
export LD_LIBRARY_PATH
PATH=~/Projects/bennugd2/build/build-linux-gnu/bin:$PATH

play_tmx_example() {
    bgdc 11-tmx.prg && bgdi 11-tmx.dcb
}
export -f play_tmx_example

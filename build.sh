#!/bin/sh

echo "Build wasm app .."
/opt/wasi-sdk/bin/clang \
    --target=wasm32-wasi \
    -O3 \
    -z stack-size=4096 \
    -Wl,--initial-memory=65536 \
    -o grayscale.wasm grayscale.c \
    -Wl,--export=main \
    -Wl,--export=__main_argc_argv \
    -Wl,--export=__data_end \
    -Wl,--export=__heap_base \
    -Wl,--strip-all \
    -Wl,--no-entry \
    -Wl,--allow-undefined \
    #-nostdlib

echo "Done"
/opt/wasi-sdk/bin/clang \
    --target=wasm32-wasi \
    -O3 \
    -Wl,--export-all,--allow-undefined \
    grayscale.c \
    -o grayscale.wasm

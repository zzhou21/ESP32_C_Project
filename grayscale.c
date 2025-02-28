#include <stdint.h>
#include <stdio.h> 

#define WASM_EXPORT __attribute__((visibility("default")))

#define BUFFER_SIZE 512
static uint8_t shared_buffer[BUFFER_SIZE];

size_t strlen(const char *s) {
    const char *end = s;
    while (*end++) ;
    return end - s - 1;
}

static inline int hex_to_int(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

WASM_EXPORT
int process_rgb_to_gray(const char* hex_input, uint32_t width, uint32_t height, uint8_t* output_buffer) {
    size_t str_len = strlen(hex_input);
    if (str_len % 2 != 0) return -1;
    
    size_t bytes_len = str_len / 2;
    if (bytes_len > BUFFER_SIZE) return -2;
    
    for (size_t i = 0; i < bytes_len; i++) {
        int high = hex_to_int(hex_input[i * 2]);
        int low = hex_to_int(hex_input[i * 2 + 1]);
        if (high == -1 || low == -1) return -3;
        shared_buffer[i] = (high << 4) | low;
    }
    
    for (size_t i = 0; i < width * height; i++) {
        const uint8_t* pixel = &shared_buffer[i * 3];
        uint32_t gray_val = (pixel[0] * 77 + pixel[1] * 150 + pixel[2] * 29) >> 8;
        output_buffer[i] = (uint8_t)gray_val;
    }
    
    return width * height;
}

//entry point
int main() {
    const char *dummy_hex = "ff0000";
    uint8_t gray_output;

    printf("testing...\n");

    int ret = process_rgb_to_gray(dummy_hex, 1, 1, &gray_output);

    if (ret < 0) {
        printf("failed with error code: %d\n", ret);
    } else {
        printf("successful. processed %d pixel(s).\n", ret);
        printf("gray value of the pixel: %d\n", gray_output);
    }
    
    return 0;
}

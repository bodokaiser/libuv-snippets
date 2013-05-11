#include <uv.h>
#include <stdio.h>

uv_loop_t* loop;

int main() {
    loop = uv_default_loop();

    uv_stream_t* stream = malloc(uv_stream_t);

    return 0;
}

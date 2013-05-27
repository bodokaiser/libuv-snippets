#include "uv.h"

uv_loop_t* loop;

uv_tcp_t tcp_req;

int main() {
    loop = uv_default_loop();

    uv_tcp_init(loop, &tcp_req);

    return uv_run(loop, UV_RUN_DEFAULT);
}

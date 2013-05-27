#include "uv.h"

uv_loop_t* loop;

uv_tcp_t tcp_req;

struct sockaddr_in addr;

int main() {
    loop = uv_default_loop();
    
    addr = uv_ip4_addr("127.0.0.1", 3000);

    uv_tcp_init(loop, &tcp_req);

    uv_tcp_bind(&tcp_req, addr);

    return uv_run(loop, UV_RUN_DEFAULT);
}

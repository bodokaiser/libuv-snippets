#include "uv.h"

uv_loop_t* loop;

uv_tcp_t tcp_req;

struct sockaddr_in addr;

void listen_cb(uv_stream_t* socket, int status);

int main() {
    loop = uv_default_loop();
    
    addr = uv_ip4_addr("127.0.0.1", 3000);

    uv_tcp_init(loop, &tcp_req);

    uv_tcp_bind(&tcp_req, addr);
    
    int r = uv_tcp_listen((uv_stream_t*) &server, 128, listen_cb);

    if (r) {
        return fprintf(stderr, "Error on listening: %s.\n", 
                uv_strerror(uv_last_error(loop)));
    }

    return uv_run(loop, UV_RUN_DEFAULT);
}

void listen_cb(uv_stream_t* socket, int status) {
    if (status == -1) {
        return fprintf(stderr, "Error on listening: %s.\n", 
                uv_strerror(uv_last_error(loop)));
    }

    /* handle connecting client */
}

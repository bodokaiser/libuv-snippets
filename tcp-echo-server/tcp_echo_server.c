#include <uv.h>
#include <stdio.h>
#include <stdlib.h>

uv_loop_t* loop;

void read_cb(uv_stream_t* stream, ssize_t nread, uv_buf_t buf);
void connection_cb(uv_stream_t* socket, int status);

int main() {
    loop = uv_default_loop();
    
    uv_tcp_t* server;
    struct sockaddr_in addr = uv_ip4_addr("127.0.0.1", 3000);

    uv_tcp_init(loop, server);
    uv_tcp_bind(server, addr);
    
    int r = uv_listen((uv_stream_t*) server, 128, connection_cb);

    if (r) {
        return fprintf(stderr, "Error on listening: %s.\n", 
                uv_strerror(uv_last_error(loop)));
    }

    return uv_run(loop, UV_RUN_DEFAULT);
}

uv_buf_t alloc_buffer(uv_handle_t* handle, size_t size) {
        return uv_buf_init((char*) malloc(size), size);
}

void connection_cb(uv_stream_t* server, int status) {
    uv_tcp_t* client;
    
    if (status == -1) {
        fprintf(stderr, "Error on listening: %s.\n", 
            uv_strerror(uv_last_error(loop)));
    }

    uv_tcp_init(loop, client);

    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        int r = uv_read_start((uv_stream_t*) client, alloc_buffer
                , read_cb);

        if (r) {
            fprintf(stderr, "Error on reading client stream: %s.\n", 
                    uv_strerror(uv_last_error(loop)));
        }
    } else {
        uv_close((uv_handle_t*) client, NULL);
    }
}

void read_cb(uv_stream_t* stream, ssize_t nread, uv_buf_t buf) {
    uv_write_t* req;
    
    if (nread == -1) {
        if (uv_last_error(loop).code != UV_EOF) {
            fprintf(stderr, "Error on reading client stream: %s.\n", 
                    uv_strerror(uv_last_error(loop)));
        }

        uv_close((uv_handle_t*) stream, NULL);
    }

    int r = uv_write(req, stream, &buf, sizeof(buf), NULL);

    if (r) {
        fprintf(stderr, "Error on writing client stream: %s.\n", 
                uv_strerror(uv_last_error(loop)));
    }

    free(buf.base);
}

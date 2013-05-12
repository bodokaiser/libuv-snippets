#include "uv.h"
#include "stdio.h"

uv_loop_t* loop;

uv_fs_t stat_req;

void stat_cb(uv_fs_t* req);

const char* path = "./";

int main() {
    loop = uv_default_loop();

    int r = uv_fs_stat(loop, &stat_req, path, stat_cb);

    if (r) {
        fprintf(stderr, "Error on reading stats: %s.\n",
                uv_strerror(uv_last_error(loop)));

        return -1;
    }

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}

void stat_cb(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error on reading stats: %s.\n",
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);

    printf("Successfully read stats.\n");
}

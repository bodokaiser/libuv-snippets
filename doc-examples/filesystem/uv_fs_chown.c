#include "uv.h"
#include "stdio.h"

uv_loop_t* loop;

uv_fs_t chown_req;

void chown_cb(uv_fs_t* req);

const char* path = "testfile";

int main() {
    loop = uv_default_loop();

    uv_fs_chown(loop, &chown_req, path, 501, 12,chown_cb);

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}

void chown_cb(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error at chaning owner of file: %s.\n",
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);

    printf("Successfully changed owner of file.\n");
}

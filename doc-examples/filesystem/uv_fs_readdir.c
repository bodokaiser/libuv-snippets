#include "uv.h"
#include "stdio.h"

uv_loop_t* loop;

uv_fs_t readdir_req;

void readdir_cb(uv_fs_t* req);

const char* path = "../filesystem";

int main() {
    loop = uv_default_loop();

    int r = uv_fs_readdir(loop, &readdir_req, path, O_RDONLY, readdir_cb);

    if (r) {
        fprintf(stderr, "Error at reading directory: %s.\n", 
                uv_strerror(uv_last_error(loop)));
        
        return -1;
    }

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}

void readdir_cb(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error at reading directory: %s.\n", 
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);

    printf("Successfully read directory content.\n");
}

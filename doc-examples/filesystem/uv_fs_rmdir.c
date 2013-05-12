#include "uv.h"
#include "stdio.h"

uv_loop_t* loop;

uv_fs_t mkdir_req;
uv_fs_t rmdir_req;

void mkdir_cb(uv_fs_t* req);
void rmdir_cb(uv_fs_t* req);

const char* path = "dir2.tmp";

int main() {
    loop = uv_default_loop();

    int r = uv_fs_mkdir(loop, &mkdir_req, path, S_IRUSR | S_IWUSR, mkdir_cb);

    if (r) {
        fprintf(stderr, "Error at creating directory: %s.\n", 
                uv_strerror(uv_last_error(loop)));
    }

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}

void mkdir_cb(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error at creating directory: %s.\n", 
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);
    uv_fs_rmdir(loop, &rmdir_req, path, rmdir_cb);
}

void rmdir_cb(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error at removing directory: %s.\n", 
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);

    printf("Successfully removed directory.\n");
}

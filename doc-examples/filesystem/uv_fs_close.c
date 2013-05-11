#include "uv.h"
#include "stdio.h"

uv_loop_t* loop;

uv_fs_t open_req;
uv_fs_t close_req;

void on_open(uv_fs_t* req);
void on_close(uv_fs_t* req);

int main() {
    loop = uv_default_loop();

    char* path = "Makefile";
    
    uv_fs_open(loop, &open_req, path, O_RDONLY, 0, on_open);

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}

void on_open(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        printf("Error occured while opening file\n");
    } else {
        printf("Successfully opened file\n");

        uv_fs_close(loop, &close_req, result, on_close);
    }

    uv_fs_req_cleanup(req);
}

void on_close(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        printf("Error occured while closing file\n");
    } else {
        printf("successfully closed file\n");
    }

    uv_fs_req_cleanup(req);
}

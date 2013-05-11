#include "uv.h"
#include "stdio.h"

uv_loop_t* loop;

uv_fs_t open_req;

void on_open(uv_fs_t* req);

int main() {
    loop = uv_default_loop();

    char* file = "Makefile";

    uv_fs_open(loop, &open_req, file, O_RDONLY, 0, on_open);

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}

void on_open(uv_fs_t* req) {
    if (!req->result == -1) {
        printf("An error occoured.\n");       
    } else {
        printf("File opened successfully.\n");
    }

    uv_fs_req_cleanup(req);
}

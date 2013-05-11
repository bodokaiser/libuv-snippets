#include "uv.h"
#include "stdio.h"

uv_loop_t* loop;

uv_fs_t open_req;
uv_fs_t read_req;
uv_fs_t close_req;

char buf[1024];

void on_open(uv_fs_t* req);
void on_read(uv_fs_t* req);
void on_close(uv_fs_t* req);

int main() {
    loop = uv_default_loop();

    uv_fs_open(loop, &open_req, "Makefile", O_RDONLY, 0, on_open);

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}

void on_open(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        printf("Error occured on opening.\n");
    } else {
        printf("Successfully opened file.\n");

        uv_fs_read(loop, &read_req, result, buf, 1024, 0, on_read);
    }

    uv_fs_req_cleanup(req);
}

void on_read(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        printf("Error occured on reading.\n");
    } else if (result == 0) {
        printf("Successfully finished reading file.\n");

        uv_fs_close(loop, &close_req, result, on_close);
    } else {
        printf("Reading file.\n");

        uv_fs_close(loop, &close_req, result, on_close);
    }

    uv_fs_req_cleanup(req);
}

void on_close(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        printf("Error occured on closing.\n");
    } else {
        printf("Successfully closed file.\n");
    }

    uv_fs_req_cleanup(req);
}

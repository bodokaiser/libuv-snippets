#include "uv.h"
#include "stdio.h"

uv_loop_t* loop;

uv_fs_t open_req;
uv_fs_t read_req;
uv_fs_t close_req;

void on_open(uv_fs_t* req);
void on_read(uv_fs_t* req);
void on_close(uv_fs_t* req);
void alloc_buffer(uv_handle_t* handle, size_t size);

int main() {
    loop = uv_default_loop();

    uv_run(loop, UV_RUN_DEFAULT);

    uv_open(loop, &open_req, "Makefile", O_RDONLY, 0, on_open);

    return 0;
}

void on_open(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        printf("An error occured while opening file.\n");
    } else {
        printf("Successfully opened file.\n");

        uv_read_start(req, alloc_buffer, on_read);
    }

    uv_req_cleanup(req);
}

void on_read(uv_fs_t* file, ssize_t nread, uv_buf_t buffer) {
    
}

void on_close(uv_fs_t* req) {

}

void alloc_buffer(uv_handle_t* handle, size_t size) {
    char* buffer = (char*) malloc(size);

    return uv_buf_init(buffer, size);
}

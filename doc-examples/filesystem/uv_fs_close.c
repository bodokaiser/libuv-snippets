#include "uv.h"
#include "stdio.h"

uv_loop_t* loop;

uv_fs_t open_req;
uv_fs_t close_req;

void on_open(uv_fs_t* req);
void on_close(uv_fs_t* req);
    
const char* path = "Makefile";

int main() {
    loop = uv_default_loop();
    
    int r = uv_fs_open(loop, &open_req, path, O_RDONLY, S_IRUSR, on_open);

    if (r) {
        fprintf(stderr, "Error on opening file: %s.\n", 
                uv_strerror(uv_last_error(loop)));
    }

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}

void on_open(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error on opening file: %s.\n", 
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);
    uv_fs_close(loop, &close_req, open_req.result, on_close);
}

void on_close(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error on closing file: %s.\n", 
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);

    printf("Successfully opened and closed a file.\n");
}

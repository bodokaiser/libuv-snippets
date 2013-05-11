#include "uv.h"
#include "stdio.h"

uv_loop_t* loop;

uv_fs_t open_req;

void on_open(uv_fs_t* req);

char* path = "Makefile";

int main() {
    loop = uv_default_loop();

    int r = uv_fs_open(loop, &open_req, path, O_RDONLY, S_IRUSR, on_open);

    if (r) {
        fprintf(stderr, "Error at opening file: %s\n",
                uv_strerror(uv_last_error(loop)));
    }

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}

void on_open(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error at opening file: %s\n",
                uv_strerror(uv_last_error(loop)));
    } 

    uv_fs_req_cleanup(req);
    
    printf("Finished opening file.\n");
}

#include "uv.h"
#include "stdio.h"

uv_loop_t* loop;

uv_fs_t open_req;
uv_fs_t read_req;
uv_fs_t close_req;

void open_cb(uv_fs_t* req);
void read_cb(uv_fs_t* req);
void close_cb(uv_fs_t* req);

char buf[1024];
const char* path = "Makefile";

int main() {
    loop = uv_default_loop();

    int r = uv_fs_open(loop, &open_req, path, O_RDONLY, S_IRUSR, open_cb);

    if (r) {
        fprintf(stderr, "Error at opening file: %s.\n", 
                uv_strerror(uv_last_error(loop)));
    }  

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}

void open_cb(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error at opening file: %s.\n", 
                uv_strerror(uv_last_error(loop)));
    }  

    uv_fs_req_cleanup(req);
    uv_fs_read(loop, &read_req, result, buf, sizeof(buf), -1, read_cb);
}

void read_cb(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error at reading file: %s.\n", 
                uv_strerror(uv_last_error(loop)));
    }         
    
    uv_fs_req_cleanup(req);
    uv_fs_close(loop, &close_req, open_req.result, close_cb);
}

void close_cb(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error at closing file: %s.\n", 
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);

    printf("Finished reading and closing file.\n");
}

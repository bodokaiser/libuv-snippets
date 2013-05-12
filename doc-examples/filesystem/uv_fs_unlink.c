#include "uv.h"
#include "stdio.h"

uv_loop_t* loop;

uv_fs_t open_req;
uv_fs_t write_req;
uv_fs_t close_req;

void open_cb(uv_fs_t* req);
void close_cb(uv_fs_t* req);
void unlink_cb(uv_fs_t* req);

char buf[] = "blablabla\n";
const char* path = "temp.txt";

int main() {
    loop = uv_default_loop();

    int r = uv_fs_open(loop, &open_req, path, O_CREAT, S_IRUSR | S_IRUSR, 
            open_cb);

    if (r) {
        fprintf(stderr, "Error opening file: %s.\n", 
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
    uv_fs_close(loop, &close_req, result, close_cb);
}

void close_cb(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error at closing file: %s.\n",
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);
    uv_fs_unlink(loop, &close_req, path, unlink_cb);
}

void unlink_cb(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error at deleting file: %s.\n",
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);

    printf("Successfuly unlinked file.\n");
}

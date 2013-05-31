#include <uv.h>
#include <stdio.h>

char buf[1024];

uv_loop_t* loop;

uv_fs_t open_req;
uv_fs_t read_req;
uv_fs_t close_req;

void open_cb(uv_fs_t* req);
void read_cb(uv_fs_t* req);
void close_cb(uv_fs_t* req);

int main(int argc, const char** argv) {
    loop = uv_default_loop();

    if (!argv[1]) {
        printf("Please pass a filename as argument.\n");

        return 1;
    }

    int r = uv_fs_open(loop, &open_req, argv[1], 
            O_RDONLY, S_IRUSR, open_cb);

    if (r) {
        fprintf(stderr, "Error on opening file: %s\n.", 
                uv_strerror(uv_last_error(loop)));
    }

    return uv_run(loop, UV_RUN_DEFAULT);
}

void open_cb(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error on opening file: %s\n.", 
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);

    int r = uv_fs_read(loop, &read_req, result, buf, 
            sizeof(buf), -1, read_cb);

    if (r) {
        fprintf(stderr, "Error on reading file: %s\n.", 
                uv_strerror(uv_last_error(loop)));
    }
}

void read_cb(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error on reading file: %s\n.", 
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);

    int r = uv_fs_close(loop, &close_req, open_req.result, close_cb);

    if (result == -1) {
        fprintf(stderr, "Error on closing file: %s\n.", 
                uv_strerror(uv_last_error(loop)));
    }
}

void close_cb(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error on closing file: %s\n.", 
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);

    printf("%s\n", buf);
}

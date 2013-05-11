#include "uv.h"
#include "stdio.h"

uv_loop_t* loop;

uv_fs_t open_req;
uv_fs_t write_req;
uv_fs_t close_req;

void on_open(uv_fs_t* req);
void on_write(uv_fs_t* req);
void on_close(uv_fs_t* req);

char buf[] = "blablabla\n";
char* path = "uv_fs_write_temp.txt";

int main() {
    loop = uv_default_loop();

    int r = uv_fs_open(loop, &open_req, path, O_WRONLY | O_CREAT, 
            S_IRUSR | S_IWUSR, on_open);

    if (r) {
        fprintf(stderr, "Error opening file: %s.\n", 
                uv_strerror(uv_last_error(loop)));
    }

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}

void on_open(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error opening file: %s.\n",
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);
    uv_fs_write(loop, &write_req, result, buf, sizeof(buf), -1, on_write);
}

void on_write(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error writting data to file: %s.\n",
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);
    uv_fs_close(loop, &close_req, open_req.result, on_close);
}

void on_close(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error closing file: %s.\n",
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);

    printf("Successfuly wrote blabla to file.\n");
}

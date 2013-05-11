#include <uv.h>
#include <stdio.h>

uv_loop_t* loop;

uv_fs_t open_req;
uv_fs_t read_req;

char buffer[1024];

void on_open(uv_fs_t* req);
void on_read(uv_fs_t* req);
void on_write(uv_fs_t* req);

int main(int argc, char **argv) {
    loop = uv_default_loop();

    char* file = argv[1];

    uv_fs_open(loop, &open_req, file, O_RDONLY, 0, on_open);

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}

void on_open(uv_fs_t* req) {
    if (req->result != -1)
        // read or write on file
    else
        // handle error
      
    uv_fs_req_cleanup(req);
}

void on_read(uv_fs_t* req) {

}

void on_write(uv_fs_t* req) {

}

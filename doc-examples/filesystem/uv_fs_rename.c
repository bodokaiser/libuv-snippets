#include "uv.h"
#include "stdio.h"

uv_loop_t* loop;

uv_fs_t open_req;
uv_fs_t close_req;
uv_fs_t rename_req;

void open_cb(uv_fs_t* req);
void close_cb(uv_fs_t* req);
void rename_cb(uv_fs_t* req);

const char* old_path = "one.tmp";
const char* new_path = "two.tmp";

int main() {
    loop = uv_default_loop();

    int r = uv_fs_open(loop, &open_req, old_path, O_CREAT | O_RDONLY, 
            S_IRUSR | S_IWUSR, open_cb);

    if (r) {
        fprintf(stderr, "Error at opening file: %s.\n",
                uv_strerror(uv_last_error(loop)));

        return -1;
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
    uv_fs_close(loop, &close_req, open_req.result, close_cb);
}

void close_cb(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error at closing file: %s.\n",
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);
    uv_fs_rename(loop, &rename_req, old_path, new_path, rename_cb);
}

void rename_cb(uv_fs_t* req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error at renaming file: %s.\n",
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);

    printf("Successfully renamed file.\n");
}

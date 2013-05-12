#include "uv_shell.h"

uv_loop_t* loop;

uv_fs_t request;

int main(int argc, const char ** argv) {
    loop = uv_default_loop();

    if (!strcmp(argv[1], "mv")) {
        uv_shell_mv(argv[2], argv[3]);
    }

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}

void print_last_error() {
    fprintf(stderr, "Error occured: %s.\n", 
            uv_strerror(uv_last_error(loop)));
}

void uv_shell_mv(const char * old_path, const char * new_path) {
    int r = uv_fs_rename(loop, &request, old_path, new_path, NULL);

    if (r) print_last_error();

    uv_fs_req_cleanup(&request);
};

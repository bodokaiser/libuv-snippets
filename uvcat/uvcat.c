#include <uv.h>
#include <stdio.h>

/**
 * Reference to our event loop.
 */
uv_loop_t * loop;

/**
 * Work requests for fs actions.
 */
uv_fs_t open_req;
uv_fs_t read_req;
uv_fs_t close_req;

/**
 * Buffer we use to read.
 */
char buf[0xffff];

/**
 * Function heads.
 */
void open_cb(uv_fs_t * req);
void read_cb(uv_fs_t * req);
void close_cb(uv_fs_t * req);

/**
 * Execution entrance point.
 * Gets passed arguments from console in argv array.
 */
int main(int argc, const char ** argv) {
    /* request our event loop */
    loop = uv_default_loop();

    /* return if user did not pass any filename */
    if (!argv[1]) {
        printf("Please pass a filename as argument.\n");

        return 1;
    }

    /* open file as user in read-only mode */
    int r = uv_fs_open(loop, &open_req, argv[1], 
            O_RDONLY, S_IRUSR, open_cb);

    /* handle error */
    if (r) {
        fprintf(stderr, "Error on opening file: %s\n.", 
                uv_strerror(uv_last_error(loop)));
    }

    /* start executing all queued tasks */
    return uv_run(loop, UV_RUN_DEFAULT);
}

/**
 * Callback executed when file is opened.
 */
void open_cb(uv_fs_t * req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error on opening file: %s\n.", 
                uv_strerror(uv_last_error(loop)));
    }

    /* free memory of our request */
    uv_fs_req_cleanup(req);

    /* read as much from the file as our buffer can handle */
    int r = uv_fs_read(loop, &read_req, result, buf, 
            sizeof(buf), -1, read_cb);

    if (r) {
        fprintf(stderr, "Error on reading file: %s\n.", 
                uv_strerror(uv_last_error(loop)));
    }
}

/**
 * Callback executed when read file.
 */
void read_cb(uv_fs_t * req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error on reading file: %s\n.", 
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);

    /* now close the file properly */
    int r = uv_fs_close(loop, &close_req, open_req.result, close_cb);

    if (result == -1) {
        fprintf(stderr, "Error on closing file: %s\n.", 
                uv_strerror(uv_last_error(loop)));
    }
}

/**
 * Callback executed when file was closed.
 */
void close_cb(uv_fs_t * req) {
    int result = req->result;

    if (result == -1) {
        fprintf(stderr, "Error on closing file: %s\n.", 
                uv_strerror(uv_last_error(loop)));
    }

    uv_fs_req_cleanup(req);

    /* output read data to console */
    printf("%s\n", buf);
}

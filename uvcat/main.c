#include <uv.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/* shared fs req structures */
uv_fs_t open_req;
uv_fs_t read_req;
uv_fs_t write_req;

/* file buffer */
char buffer[1024];

/* function prototype declarations */
void on_open(uv_fs_t *request);
void on_read(uv_fs_t *request);
void on_write(uv_fs_t *request);

/* takes provided arguments to output a file */
int main(int argc, char **argv) {
    /* set file access flag to read only */   
    int flag = O_RDONLY;
    /* set file access mode to zero */
    int mode = 0;
    /* set the filename to first argument */
    char* filename = argv[1];

    /* add file open handle to loop with above arguments */
    uv_fs_open(uv_default_loop(), &open_req, filename, flag, mode, on_open);

    /* starts executing the event loop */
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    return 0;
}

/* open file callback */
void on_open(uv_fs_t *req) {
    /* result of open request */
    int result = req->result;
    /* size of the buffer */
    int buffSize = sizeof(buffer);
    /* file read mode */
    int mode = -1;

    /* if result not an error add read handle to loop with above arguments */
    if (req->result != -1) {
        uv_fs_read(uv_default_loop(), &read_req, result, buffer, buffSize, mode, on_read);
    } else {
        fprintf(stderr, "error opening file: %d\n", req->errorno);
    }

    /* free internal memory allocation */
    uv_fs_req_cleanup(req);
}

void on_read(uv_fs_t *req) {
    /* if result smaller than zero handle error, if zero close file (EOF) and if else write to output (?) */
    if (req->result < 0) {
        fprintf(stderr, "Read error: %s\n", uv_strerror(uv_last_error(uv_default_loop())));
    } else if (req->result == 0) {
        uv_fs_t close_req;
        uv_fs_close(uv_default_loop(), &close_req, open_req.result, NULL);
    } else {
        uv_fs_write(uv_default_loop(), &write_req, 1, buffer, req->result, -1, on_write);
    }

    uv_fs_req_cleanup(req);
}

void on_write(uv_fs_t *req) {
    uv_fs_req_cleanup(req);

    if (req->result < 0) {
        fprintf(stderr, "Write error: %s\n", uv_strerror(uv_last_error(uv_default_loop())));
    } else {
        uv_fs_read(uv_default_loop(), &read_req, open_req.result, buffer, sizeof(buffer), -1, on_read);
    }
}

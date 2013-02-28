#include <uv.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* create a write_request type which contains a buffer and a write request */
typedef struct {
    uv_buf_t buffer;
    uv_write_t request;
} write_req_t;

/* define shared variables */
uv_loop_t *loop; /* ? why double use ? */
uv_pipe_t file_pipe;
uv_pipe_t stdin_pipe;
uv_pipe_t stdout_pipe;

/* function declarations */
uv_buf_t alloc_buffer(uv_handle_t *handle, size_t size);
void read_stdin(uv_stream_t *stream, ssize_t nread, uv_buf_t buffer);
void write_data(uv_stream_t *stream, size_t size, uv_buf_t buffer, uv_write_cb callback);
void on_file_write(uv_write_t *request, int status);
void on_stdout_write(uv_write_t *request, int status);
void free_write_request(uv_write_t *request);

int main(int argc, char ** argv) {
    /* contains the uv file discriptor */
    int file_discriptor;
    /* contians the file request */
    uv_fs_t file_request;
    /* contains pointer to default loop */
    uv_loop_t* loop = uv_default_loop();

    /* where does stdin_pipe come from ? */

    /* adds input pipe to loop */
    uv_pipe_init(loop, &stdin_pipe, 0);
    /* opens input pipe */
    uv_pipe_open(&stdin_pipe, 0);

    /* adds stdoutput pipe to loop */
    uv_pipe_init(loop, &stdout_pipe, 0);
    /* opens stdoutput pipe */
    uv_pipe_open(&stdout_pipe, 1);

    /* add open file task to loop with the shown parameters (is executed syncronously ?) */
    file_discriptor = uv_fs_open(loop, &file_request, argv[1], O_CREAT | O_RDWR, 0644, NULL);

    /* add fileoutput pipe to loop */
    uv_pipe_init(loop, &file_pipe, 0);
    /* open fileoutput pipe */
    uv_pipe_open(&file_pipe, file_discriptor);

    /* start begining to read incoming data of stdin. */
    /* save the incoming to a manuelly allocated buffer and call the read_stdin callback on each income */
    uv_read_start((uv_stream_t*) &stdin_pipe, alloc_buffer, read_stdin);

    /* start the loop */
    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}

/* returns a buffer instance for storing incoming stdin lines */
uv_buf_t alloc_buffer(uv_handle_t *handle, size_t size) {
    return uv_buf_init((char *) malloc(size), size);
}

/* is executed as callback on each incoming stdinput */
void read_stdin(uv_stream_t *stream, ssize_t nread, uv_buf_t buffer) {
    /* *stream pointer to current stream (stdin_pipe) ? */
    /* nread is the size of data */
    /* buffer stores the actuall data (instance from alloc_buffer?)  */
    
    /* if size is -1 close everything */
    if (nread == -1) {
        if (uv_last_error(loop).code == UV_EOF) {
            uv_close((uv_handle_t*) &file_pipe, NULL);
            uv_close((uv_handle_t*) &stdin_pipe, NULL);
            uv_close((uv_handle_t*) &stdout_pipe, NULL);
        }
    } else {
        /* write stdin input to stdout_pipe and file_pipe with size, buffer and freeing callback */
        if (nread > 0) {
            write_data((uv_stream_t*) &stdout_pipe, nread, buffer, on_stdout_write);
            write_data((uv_stream_t*) &file_pipe, nread, buffer, on_file_write);
        }
    }

    /* free the buffer */
    if (buffer.base)
        free(buffer.base);

}

/* writes the data to some streams */
void write_data(uv_stream_t *stream, size_t size, uv_buf_t buffer, uv_write_cb callback) {
    /* create a write request struct */
    write_req_t *request = (write_req_t*) malloc(sizeof(write_req_t));
    /* initialize new buffer for write request */
    request->buffer = uv_buf_init((char*) malloc(size), size);
    /* copy whole passed buffer to write request (why?) */
    memcpy(request->buffer.base, buffer.base, size);
    /* use uv_write to write something to streams */
    uv_write((uv_write_t*) request, (uv_stream_t*) stream, &request->buffer, 1, callback);
}

/* frees file write request */
void on_file_write(uv_write_t *request, int status) {
    free_write_request(request);
}

/* frees stdout write request */
void on_stdout_write(uv_write_t *request, int status) {
    free_write_request(request);
}

/* implementation of freeing algorithm */
void free_write_request(uv_write_t *request) {
    /* create a pointer to a pointer ?? WHY? */
    write_req_t *write_request = (write_req_t*) request;
    /* free structs */
    free(write_request->buffer.base);
    free(write_request);
}

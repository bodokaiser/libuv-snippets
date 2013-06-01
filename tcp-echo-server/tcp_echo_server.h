
void read_cb(uv_stream_t * stream, ssize_t nread, uv_buf_t buf);

void connection_cb(uv_stream_t * socket, int status);

uv_buf_t alloc_buffer(uv_handle_t * handle, size_t size);

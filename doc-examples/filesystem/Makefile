LDFLAGS = -luv

all: uv_fs_open uv_fs_read uv_fs_write uv_fs_close uv_fs_unlink

uv_fs_open:
	$(CC) -o uv_fs_open.o uv_fs_open.c $(LDFLAGS)

uv_fs_read:
	$(CC) -o uv_fs_read.o uv_fs_read.c $(LDFLAGS)

uv_fs_write:
	$(CC) -o uv_fs_write.o uv_fs_write.c $(LDFLAGS)

uv_fs_close:
	$(CC) -o uv_fs_close.o uv_fs_close.c $(LDFLAGS)

uv_fs_unlink:
	$(CC) -o uv_fs_unlink.o uv_fs_unlink.c $(LDFLAGS)

uv_fs_stream_read:
	$(CC) -o uv_fs_stream_read.o uv_fs_stream_read.c $(LDFLAGS)

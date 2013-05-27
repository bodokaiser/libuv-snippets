LDFLAGS = -luv

all: uv_tcp_init uv_tcp_bind

exec:
	./uv_tcp_init.o ./uv_tcp_bind.o

clean: 
	rm -Rf *.o

uv_tcp_init:
	$(CC) -o uv_tcp_init.o uv_tcp_init.c $(LDFLAGS)

uv_tcp_bind:
	$(CC) -o uv_tcp_bind.o uv_tcp_bind.c $(LDFLAGS)

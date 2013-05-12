LDFLAGS = -luv

all: uv_getaddrinfo

exec:
	./uv_getaddrinfo

clean: 
	rm -Rf *.o

uv_getaddrinfo:
	$(CC) -o uv_getaddrinfo.o uv_getaddrinfo.c $(LDFLAGS)

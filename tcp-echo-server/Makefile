LDFLAGS = -luv

build: tcp_echo_server

clean: 
	rm -Rf *.o

tcp_echo_server:
	$(CC) -o tcp_echo_server.o tcp_echo_server.c $(LDFLAGS)

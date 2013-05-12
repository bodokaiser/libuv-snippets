#include <uv.h>
#include <stdio.h>
#include <stdlib.h>

uv_loop_t* loop;

uv_getaddrinfo_t* handle;

void getaddrinfo_cb(uv_getaddrinfo_t* handle, int status, 
        struct addrinfo* response);

const char* name = "localhost";

int main() {
    loop = uv_default_loop();

    int r = uv_getaddrinfo(loop, handle, getaddrinfo_cb, name, "80", NULL);

    if (r) {
        printf("Error at dns request: %s.\n",
                uv_strerror(uv_last_error(loop)));
    }

    return 0;
}

void getaddrinfo_cb(uv_getaddrinfo_t* handle, int status,
        struct addrinfo* response) {

    printf("%s \n", handle->data);

    free(handle);
    uv_freeaddrinfo(response);
}

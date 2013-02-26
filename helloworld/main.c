#include <uv.h>
#include <stdio.h>

int main() {
    /* initialize a pointer of struct type uv_loop_t */
    uv_loop_t *loop;
    
    /* assign pointer to return pointer of uv_loop_new */
    loop = uv_loop_new();

    /* print out hello world */
    printf("Hello World\n");

    /* starts the event loop in UV_RUN_DEFAULT mode */
    uv_run(loop, UV_RUN_DEFAULT);

    /* return zero if everything went well */
    return 0;
}

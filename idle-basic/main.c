#include <uv.h>
#include <stdio.h>

/* a 64bit integer counter */
int64_t counter = 0;

/* is reexecuted until uv_idle_stop is called */
void wait_for_a_while(uv_idle_t* handle, int status) {
    counter++;

    if (counter >= 10e6)
        /* stops the idle handle */ 
        uv_idle_stop(handle);
}

int main() {
    /* a idler of uv_idle_t struct type */
    uv_idle_t idler;

    /* initialize a idle handle with the default loop and the reference of our idle type */
    uv_idle_init(uv_default_loop(), &idler);
    /* start executing the idle handler and call the wait_for_a_while callback */
    uv_idle_start(&idler, wait_for_a_while);

    printf("Idling ...\n");

    /* execute the event loop in default mode */
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}

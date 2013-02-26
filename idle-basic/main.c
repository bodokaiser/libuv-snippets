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
    /* our reference to the default loop */
    uv_loop_t *loop;

    /* a idler of uv_idle_t struct type */
    uv_idle_t idler;

    /* let uv return the default loop */
    loop = uv_default_loop();

    /* initialize a idle handle with the default loop and the reference of our idle type */
    uv_idle_init(loop, &idler);
    /* start executing the idle handler and call the wait_for_a_while callback */
    uv_idle_start(&idler, wait_for_a_while);

    printf("Idling ...\n");

    /* start runing the loop in default mode */
    uv_run(loop, UV_RUN_DEFAULT);
}

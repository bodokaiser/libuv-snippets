#include "queue.h"
#include <stdio.h>

/**
 * A pointer to a list node.
 */
static QUEUE* q;

/**
 * Our circulary list.
 */
static QUEUE queue;

/**
 * Our item struct we want to store in queue.
 */
struct user_s {
    int age;
    char* name;

    QUEUE node;
};

int main() {
    /**
     * This will be our user pointer.
     * It will point to the user we received from the queue.
     */
    struct user_s* user;

    /**
     * John is 44.
     */
    struct user_s john;
    john.name = "john";
    john.age = 44;


    /**
     * Henry is 32.
     */
    struct user_s henry;
    henry.name = "henry";
    henry.age = 32;
    
    /**
     * Willy is 99.
     */
    struct user_s willy;   
    willy.name = "willy";
    willy.age = 99;

    /**
     * Initialize the queue of each user.
     */
    QUEUE_INIT(&queue);
    QUEUE_INIT(&john.node);
    QUEUE_INIT(&henry.node);
    QUEUE_INIT(&willy.node);

    /**
     * Lets insert each user to the tail of the list.
     */
    QUEUE_INSERT_TAIL(&queue, &john.node);
    QUEUE_INSERT_TAIL(&queue, &henry.node);
    QUEUE_INSERT_TAIL(&queue, &willy.node);

    /**
     * Retrieve a pointer to our first user john.
     */
    q = QUEUE_HEAD(&queue);

    /**
     * Should retrieve the user behind the "q" pointer.
     */
    user = QUEUE_DATA(q, struct user_s, node);

    /**
     * Should output the name of john.
     */
    printf("Received first inserted user: %s who is %d.\n", 
            user->name, user->age);

    /**
     * Now lets remove john from the queue.
     */
    QUEUE_REMOVE(q);

    /**
     * Lets output the other two users through a for each loop.
     */
    QUEUE_FOREACH(q, &queue) {
        user = QUEUE_DATA(q, struct user_s, node);

        printf("Received rest inserted users: %s who is %d.\n",
            user->name, user->age);    
    }

    return 0;
}

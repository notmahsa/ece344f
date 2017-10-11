/* 
 * stoplight.c
 *
 * 31-1-2003 : GWA : Stub functions created for CS161 Asst1.
 *
 * NB: You can use any synchronization primitives available to solve
 * the stoplight problem in this file.
 */


/*
 * 
 * Includes
 *
 */

#include <types.h>
#include <lib.h>
#include <test.h>
#include <thread.h>
#include <synch.h>


/*
 *
 * Constants
 *
 */

/*
 * Number of cars created.
 */

#define NCARS 20


/*
 *
 * Function Definitions
 *
 */

static const char *directions[] = {"N", "E", "S", "W"};

static const char *msgs[] = {
    "approaching:",
    "region1:    ",
    "region2:    ",
    "region3:    ",
    "leaving:    "
};

/* use these constants for the first parameter of message */
enum {
    APPROACHING, REGION1, REGION2, REGION3, LEAVING
};
struct lock *NW;
struct lock *NE;
struct lock *SW;
struct lock *SE;

static void
message(int msg_nr, int carnumber, int cardirection, int destdirection) {
    kprintf("%s car = %2d, direction = %s, destination = %s\n",
            msgs[msg_nr], carnumber,
            directions[cardirection], directions[destdirection]);
}

/*
 * gostraight()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement passing straight through the
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
gostraight(unsigned long cardirection,
        unsigned long carnumber) {
    /*
     * Avoid unused variable warnings.
     */

    (void) cardirection;
    (void) carnumber;
//     int destdirection;
//    destdirection = cardirection + 2;
//    if (destdirection > 4) {
//        destdirection = destdirection - 4;
//    }
//
//    if (cardirection == 1) {
//        lock_acquire(NW);
//    } else if (cardirection == 2) {
//        lock_acquire(NE);
//
//    } else if (cardirection == 3) {
//        lock_acquire(SE);
//
//    } else if (cardirection == 4) {
//        lock_acquire(SW);
//    }
//    message(1, carnumber, cardirection, destdirection);
//    message(4, carnumber, cardirection, destdirection);
//    if (cardirection == 1) {
//        lock_release(NW);
//    } else if (cardirection == 2) {
//        lock_release(NE);
//
//    } else if (cardirection == 3) {
//        lock_release(SE);
//
//    } else if (cardirection == 4) {
//        lock_release(SW);
//    }
}

/*
 * turnleft()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a left turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turnleft(unsigned long cardirection,
        unsigned long carnumber) {
    /*
     * Avoid unused variable warnings.
     */

    (void) cardirection;
    (void) carnumber;
}

/*
 * turnright()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a right turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turnright(unsigned long cardirection,
        unsigned long carnumber) {
    /*
     * Avoid unused variable warnings.
     */

    (void) cardirection;
    (void) carnumber;
    int destdirection;
    destdirection = cardirection + 3;
    if (destdirection > 4) {
        destdirection = destdirection - 4;
    }

    if (cardirection == 1) {
        lock_acquire(NW);
    } else if (cardirection == 2) {
        lock_acquire(NE);

    } else if (cardirection == 3) {
        lock_acquire(SE);

    } else if (cardirection == 4) {
        lock_acquire(SW);
    }
    message(1, carnumber, cardirection, destdirection);
    message(4, carnumber, cardirection, destdirection);
    if (cardirection == 1) {
        lock_release(NW);
    } else if (cardirection == 2) {
        lock_release(NE);

    } else if (cardirection == 3) {
        lock_release(SE);

    } else if (cardirection == 4) {
        lock_release(SW);
    }
}

/*
 * approachintersection()
 *
 * Arguments: 
 *      void * unusedpointer: currently unused.
 *      unsigned long carnumber: holds car id number.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      Change this function as necessary to implement your solution. These
 *      threads are created by createcars().  Each one must choose a direction
 *      randomly, approach the intersection, choose a turn randomly, and then
 *      complete that turn.  The code to choose a direction randomly is
 *      provided, the rest is left to you to implement.  Making a turn
 *      or going straight should be done by calling one of the functions
 *      above.
 */

static
void
approachintersection(void * unusedpointer,
        unsigned long carnumber) {
    int cardirection;
    int carturn;
    int destdirection;
    /*
     * Avoid unused variable and function warnings.
     */

    (void) unusedpointer;
    (void) carnumber;
    (void) gostraight;
    (void) turnleft;
    (void) turnright;

    /*
     * cardirection is set randomly.
     */

    cardirection = random() % 4;
    carturn = random() % 3 +1;
    destdirection = cardirection + carturn;
    if (destdirection > 3) {
        destdirection = destdirection - 4;
    }

    message(0, carnumber, cardirection, destdirection);
    if (carturn == 1) {
        turnleft(cardirection, carnumber);
    } else if (carturn == 2) {
        gostraight(cardirection, carnumber);
    } else if (carturn == 3) {
        turnright(cardirection, carnumber);
    }
}

/*
 * createcars()
 *
 * Arguments:
 *      int nargs: unused.
 *      char ** args: unused.
 *
 * Returns:
 *      0 on success.
 *
 * Notes:
 *      Driver code to start up the approachintersection() threads.  You are
 *      free to modiy this code as necessary for your solution.
 */

int
createcars(int nargs,
        char ** args) {
    int index, error;

    /*
     * Avoid unused variable warnings.
     */

    NE = lock_create("NE");
    NW = lock_create("NW");
    SE = lock_create("SE");
    SW = lock_create("SW");


    (void) nargs;
    (void) args;

    /*
     * Start NCARS approachintersection() threads.
     */

    for (index = 0; index < NCARS; index++) {

        error = thread_fork("approachintersection thread",
                NULL,
                index,
                approachintersection,
                NULL
                );

        /*
         * panic() on error.
         */

        if (error) {

            panic("approachintersection: thread_fork failed: %s\n",
                    strerror(error)
                    );
        }
    }
    lock_destroy(NW);
    lock_destroy(NE);
    lock_destroy(SW);
    lock_destroy(SE);
    return 0;
}

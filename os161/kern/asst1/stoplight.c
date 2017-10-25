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
#include <queue.h>
#include <curthread.h>


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

struct queue * Nq;
struct queue * Eq;
struct queue * Sq;
struct queue * Wq;

struct cv * cv;

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
can_go_ahead() {
    //    int avail = 0;
    //    if (SW->available == 1)
    //        avail++;
    //    if (NE->available == 1)
    //        avail++;
    //    if (SE->available == 1)
    //        avail++;
    //    if (NW->available == 1)
    //        avail++;
    //    
    //    while (avail < 2){
    //        avail = 0;
    //        if (SW->available == 1)
    //            avail++;
    //        if (NE->available == 1)
    //            avail++;
    //        if (SE->available == 1)
    //            avail++;
    //        if (NW->available == 1)
    //            avail++;
    //    }
    return;
}

static
void
gostraight(unsigned long cardirection,
        unsigned long carnumber) {
    /*
     * Avoid unused variable warnings.
     */

    (void) cardirection;
    (void) carnumber;
    int destdirection;
    destdirection = cardirection + 2;
    if (destdirection > 3) {
        destdirection = destdirection - 4;
    }

    if (cardirection == 0) {
        lock_release(NE);
        can_go_ahead();
        lock_acquire(SW);
        can_go_ahead();
        lock_acquire(NW);
        message(1, carnumber, cardirection, destdirection);
        message(2, carnumber, cardirection, destdirection);
        message(4, carnumber, cardirection, destdirection);
        lock_release(NW);
        lock_release(SW);


    } else if (cardirection == 1) {
        can_go_ahead();
        lock_acquire(NE);
        can_go_ahead();
        lock_acquire(NW);
        message(1, carnumber, cardirection, destdirection);
        message(2, carnumber, cardirection, destdirection);
        message(4, carnumber, cardirection, destdirection);
        lock_release(NW);
        lock_release(NE);

    } else if (cardirection == 2) {
        can_go_ahead();
        lock_acquire(NE);
        can_go_ahead();
        lock_acquire(SE);
        message(1, carnumber, cardirection, destdirection);
        message(2, carnumber, cardirection, destdirection);
        message(4, carnumber, cardirection, destdirection);
        lock_release(SE);
        lock_release(NE);

    } else if (cardirection == 3) {
        lock_release(NE);
        can_go_ahead();
        lock_acquire(SE);
        can_go_ahead();
        lock_acquire(SW);
        message(1, carnumber, cardirection, destdirection);
        message(2, carnumber, cardirection, destdirection);
        message(4, carnumber, cardirection, destdirection);
        lock_release(SW);
        lock_release(SE);
    }

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
    int destdirection;
    destdirection = cardirection + 1;
    if (destdirection > 3) {
        destdirection = destdirection - 4;
    }


    if (cardirection == 0) {
        can_go_ahead();
        lock_acquire(SE);
        can_go_ahead();
        lock_acquire(SW);
        lock_acquire(NW);
        lock_release(NE);
        message(1, carnumber, cardirection, destdirection);
        message(2, carnumber, cardirection, destdirection);
        message(3, carnumber, cardirection, destdirection);
        message(4, carnumber, cardirection, destdirection);
        lock_release(NW);
        lock_release(SW);
        lock_release(SE);


    } else if (cardirection == 1) {
        can_go_ahead();
        lock_acquire(NE);
        can_go_ahead();
        lock_acquire(SW);
        lock_acquire(NW);
        message(1, carnumber, cardirection, destdirection);
        message(2, carnumber, cardirection, destdirection);
        message(3, carnumber, cardirection, destdirection);
        message(4, carnumber, cardirection, destdirection);
        lock_release(NW);
        lock_release(NE);
        lock_release(SW);

    } else if (cardirection == 2) {
        can_go_ahead();
        lock_acquire(NE);
        can_go_ahead();
        lock_acquire(SE);
        lock_acquire(NW);
        message(1, carnumber, cardirection, destdirection);
        message(2, carnumber, cardirection, destdirection);
        message(3, carnumber, cardirection, destdirection);
        message(4, carnumber, cardirection, destdirection);
        lock_release(SE);
        lock_release(NE);
        lock_release(NW);

    } else if (cardirection == 3) {
        can_go_ahead();
        lock_acquire(NE);
        can_go_ahead();
        lock_acquire(SE);
        lock_acquire(SW);
        message(1, carnumber, cardirection, destdirection);
        message(2, carnumber, cardirection, destdirection);
        message(3, carnumber, cardirection, destdirection);
        message(4, carnumber, cardirection, destdirection);
        lock_release(SW);
        lock_release(SE);
        lock_release(NE);
    }
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
    if (destdirection > 3) {
        destdirection = destdirection - 4;
    }


    if (cardirection == 0) {
        lock_release(NE);
        lock_acquire(NW);
        message(1, carnumber, cardirection, destdirection);
        message(4, carnumber, cardirection, destdirection);
        lock_release(NW);
    } else if (cardirection == 1) {
        lock_acquire(NE);
        message(1, carnumber, cardirection, destdirection);
        message(4, carnumber, cardirection, destdirection);
        lock_release(NE);
    } else if (cardirection == 2) {
        lock_release(NE);
        lock_acquire(SE);
        message(1, carnumber, cardirection, destdirection);
        message(4, carnumber, cardirection, destdirection);
        lock_release(SE);
    } else if (cardirection == 3) {
        lock_release(NE);
        lock_acquire(SW);
        message(1, carnumber, cardirection, destdirection);
        message(4, carnumber, cardirection, destdirection);
        lock_release(SW);
    }
}

static
void
callThread(struct cv * cv, struct thread * thread) {
    
    if (thread == q_getguy(Nq, q_getstart(Nq))) {
        if (!q_empty(Nq))
            q_remhead(Nq);
        cv_broadcast(cv, NE);
    } else if (thread == q_getguy(Eq, q_getstart(Eq))) {
        if (!q_empty(Eq))
            q_remhead(Eq);
        cv_broadcast(cv, NE);
    } else if (thread == q_getguy(Wq, q_getstart(Wq))) {
        if (!q_empty(Wq))
            q_remhead(Wq);
        cv_broadcast(cv, NE);
    } else if (thread == q_getguy(Sq, q_getstart(Sq))) {
        if (!q_empty(Sq))
            q_remhead(Sq);
        cv_broadcast(cv, NE);
    }
}

static
int
ThreadOnTop(struct thread * thread) {
    if (thread == q_getguy(Nq, q_getstart(Nq)) || thread == q_getguy(Eq, q_getstart(Eq)) ||
            thread == q_getguy(Wq, q_getstart(Wq)) || thread == q_getguy(Sq, q_getstart(Sq))) {
        kprintf("\nLOL YAH!");
        return 1;
    }
    kprintf("\nKEK NO!");
    return 0;

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
    carturn = random() % 3 + 1;
    destdirection = cardirection + carturn;
    if (destdirection > 3) {
        destdirection -= 4;
    }

    if (cardirection == 0) {
        q_addtail(Nq, curthread);
        //kprintf("\n N %d", q_getsize(Nq));
    } else if (cardirection == 1) {
        q_addtail(Eq, curthread);
        //kprintf("\n E %d", q_getsize(Eq));
    } else if (cardirection == 2) {
        q_addtail(Sq, curthread);
        //kprintf("\n S %d", q_getsize(Sq));
    } else if (cardirection == 3) {
        q_addtail(Wq, curthread);
        //kprintf("\n W %d", q_getsize(Wq));
    }

    while (ThreadOnTop(curthread) == 0) {
        if (cardirection == 0) {
            cv_wait(cv, NE);
        } else if (cardirection == 1) {
            cv_wait(cv, NE);
        } else if (cardirection == 2) {
            cv_wait(cv, NE);
        } else if (cardirection == 3) {
            cv_wait(cv, NE);
        }
    }

    message(0, carnumber, cardirection, destdirection);

    if (carturn == 1) {
        turnleft(cardirection, carnumber);
    } else if (carturn == 2) {
        gostraight(cardirection, carnumber);
    } else if (carturn == 3) {
        turnright(cardirection, carnumber);
    }

    callThread(cv, curthread);
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
    
    Nq = q_create(NCARS);
    Sq = q_create(NCARS);
    Wq = q_create(NCARS);
    Eq = q_create(NCARS);
    
    cv = cv_create("stoplight");

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
    while (!q_empty(Nq) || !q_empty(Eq) || !q_empty(Sq) || !q_empty(Wq)){
        continue;
    }
    lock_destroy(NW);
    lock_destroy(NE);
    lock_destroy(SW);
    lock_destroy(SE);
    cv_destroy(cv);
    q_destroy(Nq);
    q_destroy(Eq);
    q_destroy(Sq);
    q_destroy(Wq);
     

    return 0;
}
/*
 * catsem.c
 *
 * 30-1-2003 : GWA : Stub functions created for CS161 Asst1.
 *
 * NB: Please use SEMAPHORES to solve the cat syncronization problem in 
 * this file.
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
 * Number of food bowls.
 */

#define NFOODBOWLS 2

/*
 * Number of cats.
 */

#define NCATS 6

/*
 * Number of mice.
 */

#define NMICE 2

struct semaphore * catsema;
struct semaphore * mousesema;
struct semaphore * bowl1;
struct semaphore * bowl2;
/*
 * 
 * Function Definitions
 * 
 */

/* who should be "cat" or "mouse" */
static void
sem_eat(const char *who, int num, int bowl, int iteration) {
    kprintf("%s: %d starts eating: bowl %d, iteration %d\n", who, num,
            bowl, iteration);
    clocksleep(1);
    kprintf("%s: %d ends eating: bowl %d, iteration %d\n", who, num,
            bowl, iteration);
}

/*
 * catsem()
 *
 * Arguments:
 *      void * unusedpointer: currently unused.
 *      unsigned long catnumber: holds the cat identifier from 0 to NCATS - 1.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      Write and comment this function using semaphores.
 *
 */

static
void
catsem(void * unusedpointer,
        unsigned long catnumber) {
    /*
     * Avoid unused variable warnings.
     */

    (void) unusedpointer;
    (void) catnumber;
    int iteration = 0;
    while (iteration < 4) {
        if (mousesema->count == 0) {
            if (catsema->count < 2) {
                if (bowl1->count == 0) {
                    V(bowl1);
                    V(catsema);
                    sem_eat("cat", catnumber, 1, iteration);
                    iteration++;
                    P(bowl1);
                    P(catsema);
                }
                if (bowl2->count == 0&&iteration<4) {
                    V(bowl2);
                    V(catsema);
                    sem_eat("cat", catnumber, 2, iteration);
                    iteration++;
                    P(bowl2);
                    P(catsema);
                }
            }
        }
    }
}

/*
 * mousesem()
 *
 * Arguments:
 *      void * unusedpointer: currently unused.
 *      unsigned long mousenumber: holds the mouse identifier from 0 to 
 *              NMICE - 1.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      Write and comment this function using semaphores.
 *
 */

static
void
mousesem(void * unusedpointer,
        unsigned long mousenumber) {
    /*
     * Avoid unused variable warnings.
     */

    (void) unusedpointer;
    (void) mousenumber;
      int iteration = 0;
    while (iteration < 4) {
        if (catsema->count == 0) {
            if (mousesema->count < 2) {
                if (bowl1->count == 0) {
                    V(bowl1);
                    V(mousesema);
                    sem_eat("mouse", mousenumber, 1, iteration);
                    iteration++;
                    P(bowl1);
                    P(mousesema);
                }
                if (bowl2->count == 0&&iteration<4) {
                    V(bowl2);
                    V(mousesema);
                    sem_eat("mouse", mousenumber, 2, iteration);
                    iteration++;
                    P(bowl2);
                    P(mousesema);
                }
            }
        }
    }
}

/*
 * catmousesem()
 *
 * Arguments:
 *      int nargs: unused.
 *      char ** args: unused.
 *
 * Returns:
 *      0 on success.
 *
 * Notes:
 *      Driver code to start up catsem() and mousesem() threads.  Change this 
 *      code as necessary for your solution.
 */

int
catmousesem(int nargs,
        char ** args) {
    int index, error;

    /*
     * Avoid unused variable warnings.
     */

    (void) nargs;
    (void) args;


    catsema = sem_create("catsema", 0);
    mousesema = sem_create("mousesema", 0);
    bowl1 = sem_create("bowl1", 0);
    bowl2 = sem_create("bowl2", 0);
    /*
     * Start NCATS catsem() threads.
     */

    for (index = 0; index < NCATS; index++) {

        error = thread_fork("catsem Thread",
                NULL,
                index,
                catsem,
                NULL
                );

        /*
         * panic() on error.
         */

        if (error) {

            panic("catsem: thread_fork failed: %s\n",
                    strerror(error)
                    );
        }
    }

    /*
     * Start NMICE mousesem() threads.
     */

    for (index = 0; index < NMICE; index++) {

        error = thread_fork("mousesem Thread",
                NULL,
                index,
                mousesem,
                NULL
                );

        /*
         * panic() on error.
         */

        if (error) {

            panic("mousesem: thread_fork failed: %s\n",
                    strerror(error)
                    );
        }
    }

    return 0;
}


/*
 * End of catsem.c
 */
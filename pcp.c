#include <stdio.h>
#include <stdlib.h>

// Global semaphores and buffer count
int mutex = 1;   // mutual exclusion semaphore (1 = available, 0 = locked)
int full = 0;    // counts the number of items in buffer
int empty = 3;   // counts empty slots in buffer (buffer size = 3)
int x = 0;       // item count

// Wait operation for semaphore
int wait(int s) {
    return --s; // decrease semaphore
}

// Signal operation for semaphore
int signal(int s) {
    return ++s; // increase semaphore
}

// Producer function
void producer() {
    mutex = wait(mutex);    // enter critical section
    empty = wait(empty);    // check if buffer has empty slot
    full = signal(full);    // increase full slot count
    x++;                    // produce an item
    printf("Producer produces item %d\n", x); // print produced item
    mutex = signal(mutex);  // leave critical section
}

// Consumer function
void consumer() {
    mutex = wait(mutex);    // enter critical section
    full = wait(full);      // check if buffer has any item
    empty = signal(empty);  // increase empty slot count
    printf("Consumer consumes item %d\n", x); // print consumed item
    x--;                    // consume the item
    mutex = signal(mutex);  // leave critical section
}

// Main function
int main() {
    int choice;

    while (1) { // infinite loop until user chooses to exit
        printf("\n1. PRODUCER\n2. CONSUMER\n3. EXIT\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Check if producer can produce (mutex available and buffer not full)
                if (mutex == 1 && empty != 0)
                    producer();
                else
                    printf("Buffer is FULL\n");
                break;

            case 2:
                // Check if consumer can consume (mutex available and buffer not empty)
                if (mutex == 1 && full != 0)
                    consumer();
                else
                    printf("Buffer is EMPTY\n");
                break;

            case 3:
                exit(0); // exit program

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

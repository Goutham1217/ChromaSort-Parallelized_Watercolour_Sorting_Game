#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h> 


typedef struct {
    int colors[100];
    int top;
} Tube;

// Function to initialize a tube
void initializeTube(Tube *tube) {
    tube->top = -1;
}

// Function to check if a tube is empty
int isEmpty(Tube *tube) {
    return tube->top == -1;
}

// Function to check if a tube is full
int isFull(Tube *tube) {
    return tube->top == 99;
}
int * shuffle(int *array, size_t n) {    
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int usec = tv.tv_usec;
    srand48(usec);


    if (n > 1) {
        size_t i;
        for (i = n - 1; i > 0; i--) {
            size_t j = (unsigned int) (drand48()*(i+1));
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
    return array;
}
// Function to push a color into a tube
void push(Tube *tube, int color) {
    if (!isFull(tube)) {
        tube->colors[++(tube->top)] = color;
    }
}

// Function to pop a color from a tube
int pop(Tube *tube) {
    if (!isEmpty(tube)) {
        return tube->colors[(tube->top)--];
    }
    return -1; // Tube is empty
}

// Function to display the current state of tubes
void displayTubes(Tube tubes[], int NUM_TUBES) {
    printf("\nCurrent State of Tubes:\n");
    for (int i = 0; i < NUM_TUBES; i++) {
        printf("Tube %d: ", i + 1);
        for (int j = 0; j <= tubes[i].top; j++) {
            printf("%d ", tubes[i].colors[j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to check if all main tubes are sorted
int isSorted(Tube tubes[], int NUM_TUBES) {
    for (int i = 0; i < NUM_TUBES; i++) {
        for (int j = 0; j < tubes[i].top; j++) {
            if (tubes[i].colors[j] != tubes[i].colors[j + 1]) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    int NUM_TUBES;
    printf("Enter number of tubes: ");
    scanf("%d",&NUM_TUBES);
    int NUM_COLORS=NUM_TUBES-1;
    int ar[NUM_TUBES*NUM_COLORS];
    Tube tubes[NUM_TUBES];
    for (int i = 0; i < NUM_TUBES; i++) {
        initializeTube(&tubes[i]);
    }
    for (int i = 0; i < NUM_COLORS; i++) {
        for (int j = 0; j < NUM_TUBES; j++) {
            ar[i*NUM_TUBES+j]=i+1;
        }
    }
    int *ar1=shuffle(ar, NUM_TUBES*NUM_COLORS);
    for(int i=0; i<NUM_COLORS; i++){
        for(int j=0; j<NUM_TUBES; j++){
            tubes[i].colors[j]=*(ar+i*NUM_TUBES+j);
        }
        tubes[i].top=NUM_TUBES-1;
    }
    int moves = 0;
    while (!isSorted(tubes, NUM_TUBES)) {
        displayTubes(tubes, NUM_TUBES);

        int source, dest;
        printf("Enter source tube (1-%d) and destination tube (1-%d): ", NUM_TUBES, NUM_TUBES);
        scanf("%d %d", &source, &dest);

        if (source < 1 || source > NUM_TUBES || dest < 1 || dest > NUM_TUBES) {
            printf("Invalid tube numbers. Try again.\n");
            continue;
        }

        source--; // Convert to 0-based index
        dest--;

        int color = pop(&tubes[source]);
        if (color == -1) {
            printf("Source tube is empty. Try again.\n");
            continue;
        }

        if (!isFull(&tubes[dest])) {
            push(&tubes[dest], color);
            moves++;
        } else {
            printf("Destination tube is full. Try again.\n");
            push(&tubes[source], color); // Put the color back in the source tube
        }
    }

    printf("Congratulations! You sorted all the colors in %d moves.\n", moves);

    return 0;
}
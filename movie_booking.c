#include <stdio.h>
#include <string.h>

#define MAX 50

struct Booking {
    int id;
    char name[30];
    char movie[30];
    int seats;
};

struct Booking queue[MAX];
struct Booking stack[MAX];
int front = 0, rear = -1, count = 0;
int top = -1;
int availableSeats = 20;

void requestBooking() {
    struct Booking b;
    if (count == MAX) {
        printf("Booking queue is full!\n");
        return;
    }
    printf("Enter Booking ID: ");
    scanf("%d", &b.id);
    printf("Enter name: ");
    scanf("%s", b.name);
    printf("Enter movie: ");
    scanf("%s", b.movie);
    printf("Enter number of seats: ");
    scanf("%d", &b.seats);
    if (b.seats <= 0) {
        printf("Invalid number of seats!\n");
        return;
    }
    rear = (rear + 1) % MAX;
    queue[rear] = b;
    count++;
    printf("Booking request added to queue!\n");
}

void displayQueue() {
    int i, pos;
    if (count == 0) {
        printf("No pending booking requests.\n");
        return;
    }
    printf("ID\tName\tMovie\tSeats\n");
    for (i = 0; i < count; i++) {
        pos = (front + i) % MAX;
        printf("%d\t%s\t%s\t%d\n", queue[pos].id, queue[pos].name,
               queue[pos].movie, queue[pos].seats);
    }
}

void confirmBooking() {
    struct Booking b;
    if (count == 0) {
        printf("No pending booking requests.\n");
        return;
    }
    b = queue[front];
    if (b.seats > availableSeats) {
        printf("Not enough seats for %s! Only %d left.\n", b.name, availableSeats);
        return;
    }
    front = (front + 1) % MAX;
    count--;
    availableSeats = availableSeats - b.seats;
    top++;
    stack[top] = b;
    printf("Booking confirmed for %s (ID %d)\n", b.name, b.id);
}

void displayConfirmed() {
    int i;
    if (top == -1) {
        printf("No confirmed bookings.\n");
        return;
    }
    printf("ID\tName\tMovie\tSeats\n");
    for (i = top; i >= 0; i--) {
        printf("%d\t%s\t%s\t%d\n", stack[i].id, stack[i].name,
               stack[i].movie, stack[i].seats);
    }
}

void cancelLast() {
    if (top == -1) {
        printf("No confirmed bookings to cancel.\n");
        return;
    }
    availableSeats = availableSeats + stack[top].seats;
    printf("Cancelled booking of %s (ID %d)\n", stack[top].name, stack[top].id);
    top--;
}

void searchBooking() {
    int id, i, pos, found = 0;
    printf("Enter Booking ID to search: ");
    scanf("%d", &id);
    for (i = 0; i < count; i++) {
        pos = (front + i) % MAX;
        if (queue[pos].id == id) {
            printf("Found in pending queue: %s, %s, %d seat(s)\n",
                   queue[pos].name, queue[pos].movie, queue[pos].seats);
            found = 1;
        }
    }
    for (i = 0; i <= top; i++) {
        if (stack[i].id == id) {
            printf("Found in confirmed list: %s, %s, %d seat(s)\n",
                   stack[i].name, stack[i].movie, stack[i].seats);
            found = 1;
        }
    }
    if (found == 0)
        printf("Booking ID not found.\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n--- MOVIE TICKET BOOKING SYSTEM ---\n");
        printf("Seats available: %d\n", availableSeats);
        printf("1.Request Booking 2.Display Pending 3.Confirm Next\n");
        printf("4.Display Confirmed 5.Cancel Last 6.Search 7.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: requestBooking(); break;
            case 2: displayQueue(); break;
            case 3: confirmBooking(); break;
            case 4: displayConfirmed(); break;
            case 5: cancelLast(); break;
            case 6: searchBooking(); break;
            case 7: printf("Thank you!\n"); return 0;
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

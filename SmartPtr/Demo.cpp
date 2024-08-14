#include "Demo.h"

Demo::Demo() {
    front = 0;
    rear = 0;
    for (int i = 0; i < 16; i++) {
        ptr[i] = NULL;
    }
}

bool Demo::empty() {
    return (front == rear) && (ptr[front] == NULL);
}

bool Demo::full() {
    return (front == rear) && (ptr[front] != NULL);
}
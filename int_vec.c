#include <stdlib.h>

typedef struct INTVEC {
    int * arr;
    int size;
    int capacaty;
} int_vec;

void print_vec(int_vec v);
int_vec new_vec(int cap);
void push(int_vec * v, int n);
int contains(int_vec v, int num);
int_vec shuffle(int_vec v);

int_vec shuffle(int_vec v) {
    int_vec shuffled = new_vec(v.size);
    int_vec used = new_vec(v.size);

    for (int i = 0; i < v.size; i += 1) {
        int pos = rand() % v.size;
        while (contains(used,pos)) {
            pos += 1;
            if (pos == v.size) {
                pos = 0;
            }
        }

        push(&used, pos);
        push(&shuffled, v.arr[pos]);
    }

    return shuffled;
}

void print_vec(int_vec v) {
    printf("[");
    for (int i = 0; i < v.size; i += 1) {
        printf("%d", v.arr[i]);

        if (i+1 < v.size) {
            printf(", ");
        }
    }
    printf("]\n");
}

int_vec new_vec(int cap) {
    int_vec v;

    v.arr = malloc(cap * sizeof(int));
    v.size = 0;
    v.capacaty = cap;

    for (int i = 0; i < cap; i += 1) {
        v.arr[i] = 0;
    }

    return v;
}

void push(int_vec * v, int n) {
    v->arr[v->size] = n;
    v->size += 1;
}

int contains(int_vec v, int num) {
    int r = 0;
    for (int i = 0; i < v.size; i += 1) {
        if (v.arr[i] == num) {
            r = 1;
            break;
        }
    }

    return r;
}
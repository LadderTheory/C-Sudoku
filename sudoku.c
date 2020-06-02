#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "int_vec.c"

#ifndef SUDOKU
#define SUDOKU

int seeded = 0;

int space(int x, int y);
int_vec gen_puzzle();
void print_puzzle(int_vec p);
int_vec get_possibilities(int_vec puzzle, int pos);
void print_vec(int_vec v);

int_vec get_possibilities(int_vec puzzle, int pos) {
    int_vec bad = new_vec(9*3);

    int start;

    //horizontal
    start = pos - (pos % 9);
    for (int i = 0; i < 9; i++) {
        int n = puzzle.arr[start + i];
        if (n != 0) {
            push(&bad,n);
        }
    }

    //vertical
    start = pos % 9;
    for (int i = 0; i < 9; i += 1) {
        int n = puzzle.arr[start + (9*i)];
        //printf("n: %d | i = %d\n", n, start + i);
        if (n != 0) {
            push(&bad,n);
        }
    }

    //box
    start = pos;
    start -= (pos % 3);
    start -= ((pos / 9) % 3) * 9;
    //printf("box start: %d | pos: %d\n", start, pos);
    for (int y = 0; y < 3; y += 1) {
        for (int x = 0; x < 3; x += 1) {
            int n = puzzle.arr[start + space(x,y)];
            push(&bad, n);
        }
    }

    int_vec good = new_vec(9);

    for (int i = 1; i <= 9; i += 1) {
        if (!contains(bad, i)) {
            push(&good, i);
        }
    }

    //print_vec(good);
    if (contains(good, 0)) {
        print_vec(good);
    }
    return good;
}

int space(int x, int y) {
    return x + (9*y);
}

int_vec gen_puzzle() {
    if (!seeded) {
        srand(time(0));
        seeded = 1;
    }

    int_vec puzzle = new_vec(81);
    int_vec pospos = new_vec(81);
    int_vec possibilities[81];

    for (int i = 0; i < puzzle.capacaty; i += 1) {
        int n = 0;

        int_vec current = shuffle(get_possibilities(puzzle, i));
        if (current.size > 0) {
            n = current.arr[0];
            possibilities[i] = current;
            pospos.arr[i] = 0;
            //print_puzzle(puzzle);
            //printf("\n");
        } else {
            int backtrace = 1;

            while (backtrace) {
                i -= 1;
                puzzle.arr[i] = 0;
                if ((pospos.arr[i] + 1) < possibilities[i].size) {
                    pospos.arr[i] += 1;
                    n = possibilities[i].arr[pospos.arr[i]];
                    backtrace = 0;
                }
            }
        }

        if (n == 0) {
            printf("n");
        }
        puzzle.arr[i] = n;
    }

    //get_possibilities(puzzle, space(2,2));
    return puzzle;
}

void print_puzzle(int_vec p) {
    for (int y = 0; y < 9; y += 1) {
        for (int x = 0; x < 9; x += 1) {
            printf("%d  ", p.arr[space(x,y)]);
        }
        printf("\n");
    }
}

#endif//SUDOKU
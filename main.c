#define true 1
#define false 0

#include "sudoku.c"

int main() {
    
    for (int i = 0; i < 1000; i += 1) {
        int_vec p = gen_puzzle();
        if (false) {
            print_puzzle(p);
            printf("\n");
        }
    }

    printf("done");
}
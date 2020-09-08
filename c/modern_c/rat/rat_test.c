#include <stdio.h>
#include <stdlib.h>
#include "rationals.h"

void print_rat(rat s) {
    printf("%c%zu/%zu \n", 
            s.sign ? '-' : '+',
            s.num, 
            s.denom);
}

int main(void) {
    rat s = rat_get(-10, 25);
    print_rat(s);
    s = rat_get_normal(s);
    print_rat(s);
    s = rat_get_extended(s, 10);
    print_rat(s);
    rat r = rat_get(-3, 2);
    s = rat_get_prod(r, s);
    s = rat_get_normal(s);
    print_rat(s);

    return EXIT_SUCCESS;
}

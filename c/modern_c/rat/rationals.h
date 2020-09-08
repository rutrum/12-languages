#pragma once
#include <stdbool.h>

typedef struct rat rat;
struct rat {
    bool sign;
    size_t num;
    size_t denom;
};

rat rat_get(long long, unsigned long long);
rat rat_get_normal(rat);
rat rat_get_extended(rat, size_t);
rat rat_get_prod(rat, rat);

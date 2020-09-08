#include <stdlib.h>
#include "rationals.h"

rat rat_get(long long num, unsigned long long denom) {
    rat r = {
        .sign = (num < 0),
        .num = num < 0 ? -num : num,
        .denom = denom,
    };
    return r;
}

// shouldn't be in here I don't think
size_t gcd(size_t a, size_t b) {
    //? assert!(a > b);
    while (b != 0) {
        size_t rem = a % b;
        a = b;
        b = rem;
    }
    return a;
}

rat rat_get_normal(rat r) {
    size_t d;
    if (r.num > r.denom) {
        d = gcd(r.num, r.denom);
    } else {
        d = gcd(r.denom, r.num);
    }
    r.num /= d;
    r.denom /= d;
    return r;
}

rat rat_get_extended(rat r, size_t s) {
    r.num *= s;
    r.denom *= s;
    return r;
}

rat rat_get_prod(rat r, rat s) {
    rat p = {
        .num = r.num * s.num,
        .denom = r.denom * s.denom,
        .sign = r.sign != s.sign,
    };
    return p;
}

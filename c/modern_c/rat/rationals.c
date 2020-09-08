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

// doesn't work
rat rat_get_sum(rat r, rat s) {
    size_t lcm = r.denom * s.denom / gcd(r.denom, s.denom);
    size_t rnum = r.num * (lcm / r.denom);
    size_t snum = s.num * (lcm / s.denom);

    size_t num = rnum + snum;
    size_t sign = r.sign;
    if (rnum > snum && r.sign && !s.sign) {
        num = rnum - snum;
        sign = true;
    } else if (snum > rnum && s.sign && !r.sign) {
        num = snum - rnum;
        sign = true;
    }
    rat p = {
        .num = num,
        .denom = lcm,
        .sign = sign,
    };
    return p;
}

## Notes

### Modern C

* Pointer mutation: `const*` can't change data, `*const` can't reassign pointer, and `const*const` won't let you mutate either.
* No modules, so preface every function with a "unique" name (see the rationals.c file)
* Don't use NULL (just use 0)
* If you pass a pointer, expect mutation...but not always?  Never know, assume the worst.
* Writing in javascript preps you to write in C.  Wanna use `void*`?  You've been doing that in javascript for nearly everything.  Just write good code.

## Program Ideas

* Command line utility that transforms a floating point number (as a string) into its bit representation as a float or double.  That is, given 2233.44, write out a sign bit, the mantissa, and the exponent.  Add flags to just get the sign, mantissa, or exponent bits.  Flag to print altogether, or split by group.  Flag for 32 or 64 bit floating point.  Maybe start with doing integers of different sizes.

#include <stdint.h>


#define f ((1 << 14))


int n2fp(int n);
int x2int_zero(int x);
int x2int_nearest(int x);
int add_fp(int x, int y);
int subtract_fp(int x, int y);
int add_fp_int(int x, int n);
int subtract_int_fp(int n, int x);
int mul_fp(int x, int y);
int mul_int_fp(int x, int n);
int div_fp(int x, int y);
int div_fp_int(int x, int n);


int n2fp(int n) { 
    return n * f;
}

int x2int_zero(int x) { 
    return x / f;
}

int x2int_nearest(int x) {
    if (x >= 0) {
        return (x + f / 2) / f;
    } else {
        return (x - f / 2) / f;
    }
}

int add_fp(int x, int y) {
    return x + y;
}

int subtract_fp(int x, int y) {
    return x - y;
}

int add_fp_int(int x, int n) { 
    return x + n * f;
}

int subtract_int_fp(int n, int x) {
    return x - n * f;
}

int mul_fp(int x, int y) {
    return (int)(((int64_t) x) * y / f);
}

int mul_int_fp(int x, int n) {
    return x * n;
}

int div_fp(int x, int y) {
    return (int)(((int64_t) x) * f / y);
}

int div_fp_int(int x, int n) { 
    return x / n;
}
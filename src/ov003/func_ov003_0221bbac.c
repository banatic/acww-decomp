/* func_ov003_0221bbac @ 0x0221bbac, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096168(void *self);
extern void func_ov003_0221bfa8(void *self, int n);
extern int func_ov009_0226321c(void *self, int *a, short *s);
extern int func_ov003_02219a64(int n, int *a, int *b, short val);

typedef struct {
    char pad_00[0x2ba];
    unsigned char flag;
} SelfType;

void func_ov003_0221bbac(SelfType *self)
{
    short s;
    int a[2];
    int b[2];
    short *ps;

    if (func_02096168(self)) {
        func_ov003_0221bfa8(self, 9);
        return;
    }
    if (self->flag != 0) {
        return;
    }

    if (func_ov009_0226321c(self, a, &s)) {
        ps = &s;
        if (func_ov003_02219a64(2, a, b, *ps)) {
            self->flag = 1;
        }
    }
}

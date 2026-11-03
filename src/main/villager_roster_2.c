/* villager_roster_2: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207cd4c @ 0x0207cd4c, 0x36 bytes, Thumb
 * func_0207cd40 @ 0x0207cd40, 0xc bytes, Thumb
 * func_0207cc94 @ 0x0207cc94, 0xac bytes, Thumb
 * func_0207cc54 @ 0x0207cc54, 0x3e bytes, Thumb
 * func_0207cb9c @ 0x0207cb9c, 0xb8 bytes, Thumb
 * func_0207cb10 @ 0x0207cb10, 0x8c bytes, Thumb
 * func_0207cadc @ 0x0207cadc, 0x34 bytes, Thumb
 * func_0207cad4 @ 0x0207cad4, 0x8 bytes, Thumb
 */

typedef struct {
    unsigned char data[0x7EC];
} UnkStruct_0207cadc;

extern int func_020b6694(int);
extern int func_020b66c4(int);
extern int func_0207cf74(int);
extern int func_0207cec0(int, int);
extern int func_02080b98(int a, int b);
extern int func_0207cee4(void *self, int i);
extern int func_0207cf14(void *self, void *item);
extern int func_02003704(void *p);
extern int func_020644cc(int v);
extern void MI_CpuFill8(void *, int, unsigned int);
extern int func_0207b3dc(void *p);
extern int func_0208150c(void *p);
extern int func_0207f074(void *p);
extern int func_020951bc(void *);
extern int func_020807a8(void *, void *);
extern int func_02081d20(signed char *);

int func_0207cd4c(int param1, int param2)
{
    int result;
    unsigned char byte;
    int temp;

    result = 0;
    byte = (unsigned char) param2;
    if (func_020b6694(byte) != 0) {
        temp = func_020b66c4(byte);
        if (func_0207cf74(temp) != 0) {
            result = func_0207cec0(param1, temp);
        }
    }
    return result;
}

int func_0207cd40(int a)
{
    return func_02080b98(a, 8);
}

void *func_0207cc94(void *self, void **list, int n)
{
    int count = 0;
    int idx;
    int zero;
    int i;
    void *result = 0;
    unsigned char buf[8];

    MI_CpuFill8(buf, 0, 8);

    i = 0;
    do {
        if (func_0207cee4(self, i)) {
            buf[i] = 1;
            count++;
        }
        i++;
    } while (i < 8);

    zero = 0;
    for (i = 0; i < n; i++) {
        if (list[i]) {
            idx = func_0207cf14(self, list[i]);
            if (func_0207cf74(idx)) {
                buf[idx] = zero;
                if (func_02003704(list[i])) {
                    count--;
                }
            }
        }
    }

    if (count > 0) {
        int r = func_020644cc(count);
        for (i = 0; i < 8; i++) {
            if (buf[i] == 1) {
                if (r == 0) {
                    result = (char *) self + i * 0x7ec;
                    break;
                }
                r--;
            }
        }
    }

    return result;
}

int func_0207cc54(unsigned int a, int b, int c)
{
    int count;
    int i;
    if (b > 0) {
        count = func_020644cc(b);
        for (i = 0; i < c; i++) {
            if ((a >> i) & 1) {
                if (count == 0) {
                    return i;
                }
                count--;
            }
        }
    }
    return -1;
}

int func_0207cb9c(void *p, int *arr, int count)
{
    int i;
    unsigned char mask;
    int v;
    int b;
    unsigned char result;
    int count2;
    char *cur;
    int t;

    mask = 0;
    i = 0;
    while (i < count) {
        if (*arr != 0) {
            v = func_0207cf14(p, (void *) (*arr));
            if (func_0207cf74((unsigned int) v) != 0) {
                mask = (unsigned char) (mask | (1 << v));
            }
        }
        arr++;
        i++;
    }

    b = func_0207b3dc(p);
    if (func_0207cf74((unsigned int) b) != 0) {
        mask = (unsigned char) (mask | (1 << b));
    }

    cur = p;
    result = 0;
    count2 = 0;
    i = count2;
    do {
        t = func_0208150c(cur);
        if (((mask >> i) & 1) == 0) {
            if (func_02003704((void *) t) != 0 && func_0207f074(cur) != 0) {
                result = (unsigned char) (result | (1 << i));
                count2++;
            }
        }
        cur += 0x7ec;
        i++;
    } while (i < 8);

    return func_0207cec0((int) p, func_0207cc54(result, count2, 8));
}

void *func_0207cb10(void *p0, void *p1)
{
    signed char *tested_value0;
    int i;
    void *best = 0;

    if (func_020951bc(p1) != 0) {
        void *p = p0;
        int bestVal = -128;
        for (i = 0; i < 8; i++) {
            if (func_02003704((void *) (func_0208150c(p))) != 0) {
                if ((tested_value0 = (signed char *) (func_020807a8(p, p1))) != 0) {
                    int val = func_02081d20(tested_value0);
                    if (best == 0) {
                        best = p;
                        bestVal = val;
                    } else {
                        if (val > bestVal) {
                            best = p;
                            bestVal = val;
                        } else if (val == bestVal) {
                            if (func_020644cc(10) & 1) {
                                best = p;
                            }
                        }
                    }
                }
            }
            p = (char *) p + 0x7ec;
        }
    }

    if (best == 0) {
        best = func_0207cc94(p0, 0, 0);
    }
    return best;
}

int func_0207cadc(UnkStruct_0207cadc *p)
{
    int count;
    int i;

    count = 0;
    for (i = 0; i < 8; i++) {
        if (func_02003704((void *) (unsigned int) func_0208150c((void *) p))) {
            count++;
        }
        p++;
    }
    return count;
}

int func_0207cad4(void *argument0)
{
    return func_0207cadc((UnkStruct_0207cadc *) ((void *) argument0));
}

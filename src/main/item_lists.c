/* item_lists: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02063084 @ 0x02063084, 0x38 bytes, Thumb
 * func_0206300c @ 0x0206300c, 0x78 bytes, Thumb
 * func_02062fe8 @ 0x02062fe8, 0x24 bytes, Thumb
 */

typedef int (*Handler)(int);

struct HandlerEntry {
    char pad_00[0x10];
    Handler func;
};

typedef struct {
    unsigned char pad_00[8];
    int (*func)(int);
    unsigned char pad_0C[8];
} Entry20;

extern struct HandlerEntry data_020ccab0[];
extern int func_02063eb0(void *addr, int x);
extern int func_02063f94(int a, int b, int c);
extern int data_020cca90[];
extern unsigned char data_021dc7a8[];
extern int func_0204bcdc(void *arg);

int func_02063084(int param)
{
    unsigned int i;
    for (i = 0; i < 9; i++) {
        if (data_020ccab0[i].func(param) != 0) {
            return i;
        }
    }
    return 9;
}

int func_0206300c(int arg1, int arg2)
{
    int x;
    int result;
    unsigned int i;
    int temp;
    int zero;
    char *base;
    Entry20 *e;

    x = func_02063084(arg1);
    if (x == 9) {
        goto ret18;
    }

    base = (char *) data_021dc7a8;
    e = &((Entry20 *) data_020ccab0)[x];
    result = e->func(arg1);

    if (arg2 != 0) {
        return result;
    }

    temp = func_02063eb0(base + 0x173d4, x);
    zero = 0;

    for (i = 0; i < 3; i++) {
        if (result == func_02063f94(temp, ((int *) data_020cca90)[i], zero)) {
            return data_020cca90[i];
        }
    }
    return result;
ret18:
    return 0x18;
}

int func_02062fe8(void *arg)
{
    if (func_0204bcdc(arg) != 0 && func_0206300c((int) arg, 0) == 4) {
        return 1;
    }
    return 0;
}

/* activity_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a0340 @ 0x020a0340, 0xa0 bytes, Thumb
 * func_020a02f4 @ 0x020a02f4, 0x4c bytes, Thumb
 * func_020a02b4 @ 0x020a02b4, 0x40 bytes, Thumb
 * func_020a0284 @ 0x020a0284, 0x30 bytes, Thumb
 * func_020a0244 @ 0x020a0244, 0x40 bytes, Thumb
 */

extern int *data_020ccf94;
extern int func_02073dd4(int *g, int i);
extern int func_02073918(int *g, int i);
extern int func_020a7330(int i);
extern int func_020a72d0(int i);
extern void func_02073d6c(int *g, int i);
extern int func_02073d70(int *g);
extern int func_02075cc4(void);
extern int func_02075978(void);
extern int func_020a1954(int, char *, int);
extern int func_020984e8(void);
extern void func_02098fd0(int, int);
extern int func_0208b500(void);
extern void func_0208d0bc(int, int, int);
extern char data_020e3c2c[];
extern int func_020a01ec(void);
extern void func_02098ff8(int a, int b);
extern char data_020e3c40[];

void func_020a0340(int unused, unsigned char *p, int v, int w, int e)
{
    if (*p == v) {
        int flag = 1;
        int i = 3;
        int *g = data_020ccf94;
        while (i >= 0) {
            if (func_02073dd4(g, i) != 0 && func_02073918(g, i) == 0) {
                if (!((w == func_020a7330(i) || e == func_020a7330(i)) && func_020a72d0(i) == 0)) {
                    flag = 0;
                    break;
                }
            }
            i--;
        }
        if (flag) {
            func_02073d6c(g, 1);
            *p = v + 1;
        }
    } else {
        if (*p == v + 1 && func_02073d70(data_020ccf94) == 1 && func_02075cc4() != 0) {
            *p = v + 2;
        }
    }
}

int func_020a02f4(unsigned char *param)
{
    int result = 1;
    int i = 3;
    void *st = (*(void **) &data_020ccf94);

    for (; i >= 0; i--) {
        if (func_02073dd4((int *) st, i) != 0 && func_02073918((int *) st, i) == 0 && *(param + i + 0xf8) == 0) {
            result = 0;
            break;
        }
    }
    return result;
}

void func_020a02b4(int unused, unsigned char *p, int value)
{
    if (*p == value) {
        if (func_02073d70((int *) ((*(int *) &data_020ccf94))) == 1) {
            *p = value + 1;
        }
    } else if (*p == value + 1) {
        if (func_02075978() != 0) {
            *p = value + 2;
        }
    }
}

void func_020a0284(int a, int b)
{
    if (b == 0) {
        func_020a1954(a, data_020e3c2c, 105);
    }
    func_0208d0bc((func_02098fd0(func_020984e8(), 2), func_0208b500()), 0, 1);
}

void func_020a0244(int arg0)
{
    func_020a1954(arg0, (char *) data_020e3c40, 7);
    func_02098fd0(func_020984e8(), 2);
    if (func_020a01ec()) {
        func_0208d0bc(func_0208b500(), 0, 1);
        func_02098ff8(func_020984e8(), 2);
    }
}

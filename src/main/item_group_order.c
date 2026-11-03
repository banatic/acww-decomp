/* item_group_order: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02063f40 @ 0x02063f40, 0x54 bytes, Thumb
 * func_02063f3c @ 0x02063f3c, 0x4 bytes, Thumb
 * func_02063f18 @ 0x02063f18, 0x24 bytes, Thumb
 * func_02063ef0 @ 0x02063ef0, 0x28 bytes, Thumb
 * func_02063ed4 @ 0x02063ed4, 0x1c bytes, Thumb
 * func_02063eb8 @ 0x02063eb8, 0x1c bytes, Thumb
 */

extern int func_0205be20(void);
extern int func_0205be2c(void);
extern int FX_Div(int a, int b);
extern unsigned char data_020de63c[];
extern unsigned char *func_020640e0(int);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_0206411c(void *);
extern void func_02064120(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_02064108(unsigned char *);

unsigned char func_02063f40(unsigned int param)
{
    int a = func_0205be20();
    int sum = a + func_0205be2c();
    unsigned char byte = (unsigned char) FX_Div(sum, 0xA000);
    unsigned char arr[3];
    unsigned char *p = arr;
    arr[0] = data_020de63c[0];
    arr[1] = data_020de63c[1];
    arr[2] = data_020de63c[2];
    arr[0] = 60 - byte;
    arr[2] = byte + 10;
    if (param < 3) {
        return p[param];
    } else {
        return arr[0];
    }
}

int func_02063f3c(unsigned char *p0)
{
    return p0[0];
}

int func_02063f18(int arg0, unsigned char arg1)
{
    unsigned char *p;
    unsigned int i;
    p = func_020640e0(arg0);
    for (i = 0; i < 3; i++) {
        if (arg1 == p[i]) {
            return i + 1;
        }
    }
    return 1;
}

void *func_02063ef0(void *param)
{
    __cxa_vec_ctor((void *) (param), 9, 1, (void (*)(void *)) func_02064120, (void (*)(void *)) func_0206411c);
    return param;
}

void *func_02063ed4(void *arg)
{
    __cxa_vec_cleanup((void *) (arg), 9, 1, (void (*)(void *)) func_0206411c);
    return arg;
}

void func_02063eb8(unsigned char *ptr)
{
    unsigned int i;
    for (i = 0; i < 9; i++) {
        func_02064108(ptr + i);
    }
}

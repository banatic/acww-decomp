/* body_look: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205d058 @ 0x0205d058, 0x2a bytes, Thumb
 * func_0205d034 @ 0x0205d034, 0x24 bytes, Thumb
 * func_0205cfe8 @ 0x0205cfe8, 0x4c bytes, Thumb
 * func_0205cfd4 @ 0x0205cfd4, 0x14 bytes, Thumb
 * func_0205cfc0 @ 0x0205cfc0, 0x14 bytes, Thumb
 * func_0205cfac @ 0x0205cfac, 0x14 bytes, Thumb
 */

extern int func_0205d210(int b);
extern int func_0205d208(void);
extern int func_02064af4(int a, int b, int c);
extern int func_021077e8(unsigned int *);
extern void func_02055b50(void *p, int x);
extern int func_020b9eec(void *obj, int val, int flag);
extern int func_0205d0e0(char *, unsigned char);
extern void *func_0205d0d4(void *arg1, unsigned char arg2);
extern void *func_0205d0c8(void *param1, unsigned char param2);
extern unsigned char data_021c9c2c[];

int func_0205cfd4(unsigned char *p);
void *func_0205cfc0(unsigned char *arg);
void *func_0205cfac(unsigned char *param0);

void func_0205d058(int a, int b)
{
    int tmp1;
    int tmp2;
    tmp1 = func_0205cfd4((unsigned char *) a);
    tmp2 = func_0205d210(b);
    func_02064af4(tmp2, tmp1, func_0205d208());
}

void func_0205d034(void *p)
{
    int x;
    void *q;
    x = func_021077e8((unsigned int *) func_0205cfd4((unsigned char *) p));
    q = func_0205cfc0((unsigned char *) p);
    func_02055b50(q, x);
}

int func_0205cfe8(void *self)
{
    void *obj;
    unsigned char b;
    unsigned int f1;
    unsigned int f2;

    obj = func_0205cfac(self);
    b = ((unsigned char *) obj)[0xd];
    f1 = (b == 2) ? 1 : 0;
    if (f1) {
        return 1;
    }
    f2 = (b == 1) ? 1 : 0;
    if (f2 == 0) {
        func_020b9eec(obj, func_021077e8((unsigned int *) (func_0205cfd4((unsigned char *) self))), 1);
    }
    return 0;
}

int func_0205cfd4(unsigned char *p)
{
    return func_0205d0e0(((char *) data_021c9c2c), *p);
}

void *func_0205cfc0(unsigned char *arg)
{
    return func_0205d0d4(((unsigned char *) data_021c9c2c), *arg);
}

void *func_0205cfac(unsigned char *param0)
{
    unsigned char value;
    void *global_ptr;

    value = *param0;
    global_ptr = (void *) data_021c9c2c;
    return func_0205d0c8(global_ptr, value);
}

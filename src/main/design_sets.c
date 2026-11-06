/* design_sets: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020728e8 @ 0x020728e8, 0x10 bytes, Thumb
 * func_020728d8 @ 0x020728d8, 0x10 bytes, Thumb
 * func_02072830 @ 0x02072830, 0xa8 bytes, Thumb
 * func_0207282c @ 0x0207282c, 0x2 bytes, Thumb
 * func_02072824 @ 0x02072824, 0x8 bytes, Thumb
 * func_02072808 @ 0x02072808, 0x1c bytes, Thumb
 * func_020727ec @ 0x020727ec, 0x1c bytes, Thumb
 * func_020727d4 @ 0x020727d4, 0x18 bytes, Thumb
 * func_020727b8 @ 0x020727b8, 0x1c bytes, Thumb
 * func_020727a4 @ 0x020727a4, 0x14 bytes, Thumb
 * func_0207277c @ 0x0207277c, 0x28 bytes, Thumb
 */

extern char *func_02072dbc(int param);
extern void *func_02072da4(int n);
extern void *func_020e98b4(unsigned int);
extern void func_020721ac(void);
extern int func_02072180(void *, int);
extern void *func_02072da0(void *object);
extern int func_0207216c(void *, int);
extern int func_02072260(void);
extern int func_02072d4c(void *);
extern int func_02072268(int, int, int);
extern void *func_02072ee8(void *record);
extern void *func_02095040(void *record);
extern void func_02064290(int, unsigned short);
extern void func_020950cc(int, unsigned short);
extern void func_020e9898(void *);
extern unsigned short data_020ccb64;
extern unsigned short data_020d185c;
extern int data_021d0800;
extern void func_02072600(void *ptr);
extern void func_0207252c(void *receiver);
extern int func_02072578(char *p);
extern void *func_020725f0(char *p);
extern void func_020725ec(char *p);
extern void func_02072574(void *receiver);
extern unsigned char data_021d0478[4];
extern unsigned char data_021d0468;

void *func_0207282c(void *record);
void func_020727b8(void *receiver);

int func_020728e8(int param)
{
    func_02072dbc(param);
    return param;
}

int func_020728d8(int n)
{
    func_02072da4(n);
    return n;
}

int func_02072830(void *r5, unsigned int r6)
{
    void *r4;
    int a, b;

    if (r6 < 0x20) {
        r4 = func_020e98b4(0x200);
        if (r4 == 0) {
            goto ret1;
        }
        if (r4 != 0) {
            func_020721ac();
        }

        func_02072180(r4, r6);

        a = (int) func_02072da0(func_0207282c(r5));
        func_0207216c(r4, a);

        b = func_02072260();

        a = func_02072d4c(func_0207282c(r5));
        r6 += 0x12;
        func_02072268(b, a, r6);

        func_02064290((int) func_02095040(func_02072ee8((void *) func_02072d4c(func_0207282c(r5)))), data_020ccb64);
        func_020950cc((int) func_02072ee8((void *) func_02072d4c(func_0207282c(r5))), data_020d185c);

        func_020e9898(r4);
    ret1:
        return 1;
    }
    return 0;
}

void *func_0207282c(void *record)
{
    return record;
}

int func_02072824(void)
{
    return (int) &data_021d0800;
}

void func_02072808(void *arg)
{
    func_02072600((char *) arg + 4);
    func_0207252c(arg);
    func_020727b8(arg);
}

char *func_020727ec(char *p)
{
    func_02072578(p);
    func_020725f0(p + 4);
    func_02072808((void *) p);
    return p;
}

char *func_020727d4(char *p)
{
    func_020725ec(p + 4);
    func_02072574(p);
    return p;
}

void func_020727b8(void *receiver)
{
    unsigned int i = 0;
    unsigned int v = i;
    do {
        data_021d0478[i] = (unsigned char) v;
        i++;
    } while (i < 4);
    data_021d0468 = (unsigned char) v;
}

void func_020727a4(int param0, int param1)
{
    data_021d0468 |= (1 << param1);
}

int func_0207277c(int a, int bit)
{
    int r;
    if ((((*(volatile unsigned char *) &data_021d0468) >> bit) & 1) != 0) {
        r = 1;
    } else {
        r = 0;
    }
    (*(volatile unsigned char *) &data_021d0468) =
        (unsigned char) ((*(volatile unsigned char *) &data_021d0468) & ~(1 << bit));
    return r;
}

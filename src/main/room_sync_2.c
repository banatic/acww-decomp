/* room_sync_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02052078 @ 0x02052078, 0x28 bytes, Thumb
 * func_02052038 @ 0x02052038, 0x40 bytes, Thumb
 * func_02051f74 @ 0x02051f74, 0xc4 bytes, Thumb
 * func_02051f4c @ 0x02051f4c, 0x28 bytes, Thumb
 */

extern int func_02060bf8(int *p, int a, int b);
extern void func_020520a0(int a, int b, int c);
extern int data_021ebcd4;
extern int func_02073d90(int);
extern int func_02073918(int, int);
extern int data_020ccf94;
extern int func_020a7278(void);
extern void func_0205298c(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, int a4);
extern void *func_ov004_0223cd50(void);
extern void *func_ov004_0223cc10(void *p, unsigned int a1, unsigned int a2, unsigned int a3);
extern void func_02073820(void *p);
extern void func_020737f0(void *p, unsigned short *flags, int mode);
extern void func_02073770(void *p, int id, int val);
extern void func_0204f818(int *, int *, int);

void func_02052078(int a, int b)
{
    func_02060bf8(&data_021ebcd4, a, b);
    func_020520a0(a, b, 4);
}

void func_02052038(int x, int y)
{
    int a;
    a = data_020ccf94;
    if (func_02073d90(a) == 0 || func_02073918(a, 0) != 0) {
        func_02052078(x, y);
    } else {
        func_020520a0(x, y, 0);
    }
}

void func_02051f74(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3)
{
    void *p;
    void *q;
    unsigned short flags;
    void *base;

    if (!func_02073d90((int) ((*(void **) &data_020ccf94))) || func_020a7278()) {
        func_0205298c(a0, a1, a2, a3, 1);
        return;
    }
    p = func_ov004_0223cd50();
    q = func_ov004_0223cc10(p, a1, a2, a3);
    if (q) {
        ((char *) q)[0x77d] = 1;
    }

    flags = (flags & ~0x3f) | (a0 & 0x3f);
    flags = (flags & ~0x40) | ((a3 & 1) << 6);
    flags = (flags & ~0x780) | (((unsigned short) a1 & 0xf) << 7);
    flags = (flags & ~0x7800) | (((unsigned short) a2 & 0xf) << 11);

    base = (*(void **) &data_020ccf94);
    func_02073820(base);
    func_020737f0(base, &flags, 2);
    func_02073770(base, 0x1d, 6);
}

void func_02051f4c(int a, int b, int c)
{
    int sp0;
    int sp4;

    func_0204f818(&sp0, &sp4, b);
    func_02051f74(a, sp0, sp4, c);
}

/* func_02051f74 @ 0x02051f74, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(void *p);
extern int func_020a7278(void);
extern void func_0205298c(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, int a4);
extern void *func_ov004_0223cd50(void);
extern void *func_ov004_0223cc10(void *p, unsigned int a1, unsigned int a2, unsigned int a3);
extern void func_02073820(void *p);
extern void func_020737f0(void *p, unsigned short *flags, int mode);
extern void func_02073770(void *p, int id, int val);
extern void *data_020ccf94;

void func_02051f74(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3)
{
    void *p;
    void *q;
    unsigned short flags;
    void *base;

    if (!func_02073d90(data_020ccf94) || func_020a7278()) {
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

    base = data_020ccf94;
    func_02073820(base);
    func_020737f0(base, &flags, 2);
    func_02073770(base, 0x1d, 6);
}

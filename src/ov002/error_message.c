/* error_message: 7 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_0220b740 @ 0x0220b740, 0xc bytes, Thumb
 * func_ov002_0220b738 @ 0x0220b738, 0x8 bytes, Thumb
 * func_ov002_0220b71c @ 0x0220b71c, 0x1c bytes, Thumb
 * func_ov002_0220b6f4 @ 0x0220b6f4, 0x28 bytes, Thumb
 * func_ov002_0220b6d0 @ 0x0220b6d0, 0x24 bytes, Thumb
 * func_ov002_0220b6b8 @ 0x0220b6b8, 0x16 bytes, Thumb
 * func_ov002_0220b6b0 @ 0x0220b6b0, 0x8 bytes, Thumb
 */

extern int func_ov002_02207d24(int a, int b);
extern int *func_020682e0(int which);
extern int func_02068484(void *p, void *q, int x);
extern void func_02068428(void *p);
extern void func_02068434(void *p);
extern char data_021f43e8;
extern void func_02068320(void *p);
extern void func_02001a1c(int);
extern void func_02001a7c(void);
extern void func_02001a5c(void);

void func_ov002_0220b6b0(void *self);

int func_ov002_0220b740(int a)
{
    return func_ov002_02207d24(a, 0);
}

void func_ov002_0220b738(void *self)
{
    func_ov002_0220b6b0(self);
}

int func_ov002_0220b71c(void *self)
{
    if (func_020682e0(1)[1] == 2) {
        return 1;
    }
    return 0;
}

void func_ov002_0220b6f4(void)
{
    void *p = (void *) func_020682e0(1);

    func_02068484(p, &data_021f43e8, 0);
    func_02068428(p);
    func_02068434(p);
}

int func_ov002_0220b6d0(char *self)
{
    int *p = *(int **) (self + 0x110);

    if (p[1] == 0) {
        func_02068320(p);
        return 1;
    }
    return 0;
}

void func_ov002_0220b6b8(void *receiver)
{
    // DECLS
    // ENDDECLS
    func_02001a7c();
    func_02001a1c(-0xa);
}

void func_ov002_0220b6b0(void *self)
{
    func_02001a5c();
}

/* letter_pick_2: 5 functions, module ov108
 * mwccarm 1.2/base -O4,s
 * func_ov108_0229c72c @ 0x0229c72c, 0x68 bytes, Thumb
 * func_ov108_0229c6d8 @ 0x0229c6d8, 0x54 bytes, Thumb
 * func_ov108_0229c674 @ 0x0229c674, 0x64 bytes, Thumb
 * func_ov108_0229c628 @ 0x0229c628, 0x4c bytes, Thumb
 * func_ov108_0229c5f4 @ 0x0229c5f4, 0x34 bytes, Thumb
 */

struct UnkStruct_0229c72c {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x222];
    unsigned char unk_2B0;
    unsigned char pad_2B1[2];
    unsigned char unk_2B3;
    unsigned char pad_2B4[0x21e4];
    unsigned char sub_2498[1];
};

extern void func_ov002_0220a314(void *ptr);
extern void func_ov002_0220a2b4(void *ptr);
extern void func_ov002_0220a05c(void *ptr, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov108_0229c7c8(void *ptr);
extern int func_ov108_0229c7b8(void *ptr);
extern int func_ov002_0220a08c(unsigned char *addr, int a1, int a2, int a3);
extern int func_ov002_022090e4(void *, int);
extern int func_ov002_02208ae4(void *ptr);
extern int func_ov002_02208ad8(void *ptr, unsigned char val);
extern void func_ov002_0220a0b4(void *ptr, int arg1, int arg2);
extern void func_0208e4c0(void *ptr, int arg);
extern void func_ov002_0220a374(void *p, int a);

void func_ov108_0229c72c(struct UnkStruct_0229c72c *p)
{
    if (p->unk_2B0 == 0x15) {
        func_ov002_0220a314(&p->sub_2498);
    } else {
        func_ov002_0220a2b4(&p->sub_2498);
    }
    {
        int a = func_ov108_0229c7c8(p);
        int b = func_ov108_0229c7b8(p);
        func_ov002_0220a05c(&p->sub_2498, a, b, 3, 1);
    }
    p->unk_2B3 = p->unk_8D;
    func_ov002_02208098((void *) (p), 0xa);
}

void func_ov108_0229c6d8(unsigned char *self)
{
    int t1;
    int t2;
    t1 = func_ov002_02208ae4((void *) (self + 0x24fc));
    t2 = func_ov002_02208ad8((void *) (self + 0x24fc), self[0x2b5]);
    func_ov002_0220a08c(self + 0x2498, t1, t2, 2);
    self[0x2b3] = self[0x8d];
    func_ov002_02208098((void *) (self), 0xa);
}

void func_ov108_0229c674(unsigned char *self)
{
    int x;

    self[0x2B4] = 1;
    self[0x2B5] = (unsigned char) func_ov002_022090e4(self + 0x24FC, 1);
    x = func_ov002_02208ae4(self + 0x24FC);
    func_ov002_0220a0b4(self + 0x2498, x, func_ov002_02208ad8(self + 0x24FC, self[0x2B5]));
    func_0208e4c0(self + 0x2498, 8);
    func_ov002_02208098((void *) (self), 0x14);
}

void func_ov108_0229c628(unsigned char *obj)
{
    int result1;
    int result2;

    obj[0x2b5] = 0;
    result1 = func_ov002_02208ae4(obj + 0x24fc);
    result2 = func_ov002_02208ad8(obj + 0x24fc, obj[0x2b5]);
    func_ov002_0220a0b4(obj + 0x2498, result1, result2);
    func_ov002_0220a374(obj + 0x2498, 7);
}

void func_ov108_0229c5f4(int arg0)
{
    int local_0;
    int local_1;
    int local_2;

    local_0 = func_ov108_0229c7c8((void *) arg0);
    local_1 = func_ov108_0229c7b8((void *) arg0);
    func_ov002_0220a0b4((void *) (arg0 + 0x2498), local_0, local_1);
    func_ov002_0220a374((void *) (arg0 + 0x2498), 1);
}

/* pockets_view_2: 4 functions, module ov099
 * mwccarm 1.2/base -O4,s
 * func_ov099_0229c6dc @ 0x0229c6dc, 0x78 bytes, Thumb
 * func_ov099_0229c688 @ 0x0229c688, 0x54 bytes, Thumb
 * func_ov099_0229c63c @ 0x0229c63c, 0x4c bytes, Thumb
 * func_ov099_0229c608 @ 0x0229c608, 0x34 bytes, Thumb
 */

struct UnkStruct_0229c63c {
    char pad_00[0x2274];
    char unk_2274;
    char pad_2275[0x63];
    char unk_22D8;
    char pad_22D9[0x633];
    unsigned char flag;
};

extern int func_ov099_0229c2ac(void *p, int n);
extern int func_ov099_0229c788(void *p);
extern int func_ov099_0229c778(void *p);
extern void func_ov099_0229c28c(void *p, int n);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern int func_ov002_02208ae4(void *);
extern int func_ov002_02208ad8(void *, unsigned char);
extern int func_ov002_0220a08c(void *, int, int, int);
extern void func_ov002_0220a374(void *, int);

void func_ov099_0229c6dc(void *base)
{
    if (func_ov099_0229c2ac(base, 8)) {
        int first = func_ov099_0229c788(base);
        int second = func_ov099_0229c778(base);
        func_ov002_0220a0b4((void *) ((char *) base + 0x2274), first, second);
        func_ov099_0229c28c(base, 8);
    } else {
        int first = func_ov099_0229c788(base);
        int second = func_ov099_0229c778(base);
        func_ov002_0220a05c((void *) ((char *) base + 0x2274), first, second, 3, 1);
        *((unsigned char *) base + 0x290a) = *((unsigned char *) base + 0x8d);
        func_ov002_02208098(base, 8);
    }
}

// placeholder for r5 base
void func_ov099_0229c688(char *base)
{
    int r4;
    int r2;
    unsigned char b;

    r4 = func_ov002_02208ae4(base + 0x22d8);
    r2 = func_ov002_02208ad8(base + 0x22d8, *(unsigned char *) (base + 0x290c));
    func_ov002_0220a08c(base + 0x2274, r4, r2, 2);
    b = *(unsigned char *) (base + 0x8d);
    *(unsigned char *) (base + 0x290a) = b;
    func_ov002_02208098(base, 8);
}

void func_ov099_0229c63c(struct UnkStruct_0229c63c *self)
{
    int a;
    int b;
    self->flag = 0;
    a = func_ov002_02208ae4(&self->unk_22D8);
    b = func_ov002_02208ad8(&self->unk_22D8, self->flag);
    func_ov002_0220a0b4(&self->unk_2274, a, b);
    func_ov002_0220a374(&self->unk_2274, 7);
}

void func_ov099_0229c608(char *param)
{
    int a = func_ov099_0229c788((void *) param);
    int b = func_ov099_0229c778((void *) param);
    func_ov002_0220a0b4(param + 0x2274, a, b);
    func_ov002_0220a374(param + 0x2274, 1);
}

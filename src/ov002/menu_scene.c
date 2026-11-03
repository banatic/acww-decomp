/* menu_scene: 24 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_02208090 @ 0x02208090, 0x6 bytes, Thumb
 * func_ov002_02208054 @ 0x02208054, 0x3c bytes, Thumb
 * func_ov002_02208014 @ 0x02208014, 0x40 bytes, Thumb
 * func_ov002_02208008 @ 0x02208008, 0xc bytes, Thumb
 * func_ov002_02207ffc @ 0x02207ffc, 0xc bytes, Thumb
 * func_ov002_02207ff0 @ 0x02207ff0, 0xc bytes, Thumb
 * func_ov002_02207fe4 @ 0x02207fe4, 0xc bytes, Thumb
 * func_ov002_02207fd8 @ 0x02207fd8, 0xc bytes, Thumb
 * func_ov002_02207fc0 @ 0x02207fc0, 0x16 bytes, Thumb
 * func_ov002_02207fb0 @ 0x02207fb0, 0x10 bytes, Thumb
 * func_ov002_02207f80 @ 0x02207f80, 0x30 bytes, Thumb
 * func_ov002_02207f6c @ 0x02207f6c, 0x14 bytes, Thumb
 * func_ov002_02207f60 @ 0x02207f60, 0xc bytes, Thumb
 * func_ov002_02207f54 @ 0x02207f54, 0xc bytes, Thumb
 * func_ov002_02207f48 @ 0x02207f48, 0xc bytes, Thumb
 * func_ov002_02207f3c @ 0x02207f3c, 0xc bytes, Thumb
 * func_ov002_02207f20 @ 0x02207f20, 0x1c bytes, Thumb
 * func_ov002_02207f04 @ 0x02207f04, 0x1c bytes, Thumb
 * func_ov002_02207ee8 @ 0x02207ee8, 0x1c bytes, Thumb
 * func_ov002_02207ecc @ 0x02207ecc, 0x1c bytes, Thumb
 * func_ov002_02207eb4 @ 0x02207eb4, 0x18 bytes, Thumb
 * func_ov002_02207e9c @ 0x02207e9c, 0x18 bytes, Thumb
 * func_ov002_02207e90 @ 0x02207e90, 0xc bytes, Thumb
 * func_ov002_02207e80 @ 0x02207e80, 0x10 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x8c];
    unsigned char flags;
} UnkStruct_02208090;

struct UnkStruct_02208054 {
    unsigned short pad_00; // offset 0
    unsigned short val;    // offset 2
};

struct UnkStruct_02207eb4 {
    char pad_00[0x70];
    int value;
};

extern void func_0206fe7c(void);
extern void func_0200467c(int);
extern struct UnkStruct_02208054 data_021fbe40;
extern void func_0206fe90(void);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern char *func_ov002_0220892c(char *p);
extern int func_ov002_02208918(int);
extern int func_ov002_02208904(void *ptr);
extern int func_ov002_022088f0(void *);
extern int func_ov002_022088dc(void *p);
extern void func_ov002_02208880(void *p, int a, int b, int c);
extern int func_020e9958(int a, int b);
extern int memset(int a, int b, int c);
extern void func_020e993c(void *a1, void *a2);
extern unsigned char data_021c9b28[];
extern int func_ov002_02208780(void *p);
extern int func_ov002_02208764(void *ptr);
extern int func_ov002_0220866c(void *p, int kind);
extern int func_ov002_02208594(void *, int parameter1);
extern void func_ov002_02208558(void *r0, int r1, int r2, int r3, int r4);
extern void func_ov002_0220851c(int p0, int p1, int p2, int p3, int p4);
extern void func_ov002_022084e4(char *arg0, int arg1, int arg2, int arg3, int arg4);
extern void func_ov002_02208498(void *a, int b, int c, int d, int e);
extern void func_ov002_02208458(void *, int, int, int);
extern void func_ov002_02208418(char *a, int b, int c, int d);
extern void func_ov002_02208344(void *, int parameter1);
extern void func_ov002_022083b8(void *p, int a, int b, int c);

void func_ov002_02208090(UnkStruct_02208090 *p, unsigned char v)
{
    p->flags = v;
}

int func_ov002_02208054(int unused, int p)
{
    int masked;
    masked = data_021fbe40.val & 0xFFF;
    if (masked) {
        func_0206fe7c();
        func_0200467c(0x866);
        if (p != 0) {
            func_0200467c(0x3B);
        }
        return 1;
    } else {
        return 0;
    }
}

int func_ov002_02208014(void *receiver)
{
    unsigned int cond = (data_021fbdd8 != 0) && (data_021fbddc != 0);
    if (cond > 0) {
        func_0206fe90();
        func_0200467c(0x866);
        return 1;
    }
    return 0;
}

char *func_ov002_02208008(char *p)
{
    return func_ov002_0220892c(p + 0x50);
}

int func_ov002_02207ffc(int arg)
{
    return func_ov002_02208918(arg + 0x50);
}

int func_ov002_02207ff0(void *ptr)
{
    return func_ov002_02208904((char *) ptr + 0x50);
}

int func_ov002_02207fe4(void *arg)
{
    return func_ov002_022088f0((char *) arg + 0x50);
}

int func_ov002_02207fd8(void *p)
{
    return func_ov002_022088dc((char *) p + 0x50);
}

void func_ov002_02207fc0(void *p)
{
    func_ov002_02208880((char *) p + 0x50, 8, 1, 7);
}

void func_ov002_02207fb0(void *p, int a, int b, int c)
{
    func_ov002_02208880((char *) p + 0x50, a, b, c);
}

int func_ov002_02207f80(int param)
{
    int res;
    res = func_020e9958((*(int *) data_021c9b28), param);
    if (res == 0) {
        return 0;
    }
    memset(res, 0, param);
    return res;
}

void func_ov002_02207f6c(void *a1)
{
    void *v1 = a1;
    void *v2 = *(void **) data_021c9b28;
    func_020e993c(v2, v1);
}

int func_ov002_02207f60(void *p)
{
    return func_ov002_02208780((char *) p + 0x70);
}

int func_ov002_02207f54(void *self)
{
    return func_ov002_02208764((char *) self + 0x70);
}

int func_ov002_02207f48(void *p, int kind)
{
    return func_ov002_0220866c((char *) p + 0x70, kind);
}

int func_ov002_02207f3c(void *p, int arg1)
{
    return func_ov002_02208594((char *) p + 0x70, arg1);
}

void func_ov002_02207f20(void *r0, int r1, int r2, int r3, int r4)
{
    if (r2 == 0) {
        r2 = 4;
    }
    func_ov002_02208558((char *) r0 + 0x70, r1, r2, r3, r4);
}

void func_ov002_02207f04(int p0, int p1, int p2, int p3, int p4)
{
    if (p2 == 0) {
        p2 = 3;
    }
    func_ov002_0220851c(p0 + 0x70, p1, p2, p3, p4);
}

void func_ov002_02207ee8(char *a, int b, int c, int d, int e)
{
    if (c == 0) {
        c = 4;
    }
    func_ov002_022084e4(a + 0x70, b, c, d, e);
}

void func_ov002_02207ecc(void *r0, int r1, int r2, int r3, int r4)
{
    if (r2 == 0) {
        r2 = 3;
    }
    func_ov002_02208498((char *) r0 + 0x70, r1, r2, r3, r4);
}

void func_ov002_02207eb4(struct UnkStruct_02207eb4 *a, int b, int c)
{
    if (b == 0) {
        b = 4;
    }
    func_ov002_02208458(&a->value, b, c, 0x30);
}

void func_ov002_02207e9c(char *a, int b, int c)
{
    if (b == 0) {
        b = 3;
    }
    func_ov002_02208418(a + 0x70, b, c, 0x30);
}

void func_ov002_02207e90(void *p, int arg1)
{
    func_ov002_02208344((char *) p + 0x70, arg1);
}

void func_ov002_02207e80(void *p, int a, int b, int c)
{
    func_ov002_022083b8((char *) p + 0x70, a, b, c);
}

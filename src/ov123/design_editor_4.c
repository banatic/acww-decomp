/* design_editor_4: 11 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_0229a2f8 @ 0x0229a2f8, 0x48 bytes, Thumb
 * func_ov123_0229a2b4 @ 0x0229a2b4, 0x44 bytes, Thumb
 * func_ov123_0229a278 @ 0x0229a278, 0x3c bytes, Thumb
 * func_ov123_0229a248 @ 0x0229a248, 0x2e bytes, Thumb
 * func_ov123_0229a224 @ 0x0229a224, 0x24 bytes, Thumb
 * func_ov123_0229a1f4 @ 0x0229a1f4, 0x30 bytes, Thumb
 * func_ov123_0229a1e8 @ 0x0229a1e8, 0xc bytes, Thumb
 * func_ov123_0229a180 @ 0x0229a180, 0x68 bytes, Thumb
 * func_ov123_0229a148 @ 0x0229a148, 0x38 bytes, Thumb
 * func_ov123_0229a0cc @ 0x0229a0cc, 0x7c bytes, Thumb
 * func_ov123_0229a094 @ 0x0229a094, 0x38 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xA4];
    volatile unsigned char unk_A4;
} UnkStruct_0229a278;

struct UnkStruct_0229a1f4 {
    unsigned char pad_00[0xa7];
    unsigned char unk_A7;
};

struct FuncOv123Data {
    unsigned short pad_00;
    unsigned short : 9;
    unsigned short field : 5;
    unsigned short : 2;
};

extern unsigned char data_ov123_0229c9c4[];
extern unsigned char data_ov123_0229c9a4[];
extern unsigned char data_ov123_0229c9b4[];
extern void func_0206fdd4(char *p, unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4, unsigned int v5);
extern void func_ov123_02299640(char *a, int x);
extern int func_ov123_02299650(void *p, int n);
extern int func_020b9bbc(void *a, void *b, int c, int d, int e);
extern void func_ov123_02299630(void *p, int n);
extern void func_0200467c(int);
extern void func_02070b84(void *ptr);
extern int func_ov123_0229ae7c(int, int);
extern int func_ov123_0229ae74(int, int);
extern int func_020896b8(int, void *, int, int, int, int, int);
extern struct FuncOv123Data data_ov123_0229cf20;
extern const unsigned short data_ov123_0229cea0[];
extern int data_ov123_0229cf08;
extern void func_02088df8(int a, int *b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l);
extern int *data_ov123_0229cfec[];
extern int data_ov123_0229ce90[];
extern int data_ov123_0229ceb0;

void func_ov123_0229a224(unsigned char *obj);

void func_ov123_0229a2f8(char *a, unsigned int b, unsigned int c)
{
    if (b > 12) {
        return;
    }
    func_0206fdd4(a + 0x230, data_ov123_0229c9a4[b], data_ov123_0229c9c4[b], data_ov123_0229c9b4[b],
                  data_ov123_0229c9c4[b] + 2, c);
    func_ov123_02299640(a, 16);
}

void func_ov123_0229a2b4(char *p)
{
    if (func_ov123_02299650(p, 0x10) == 0) {
        return;
    }
    if (func_020b9bbc(p + 0x194, p + 0x230, 6, 0x800, 0) != 0) {
        func_ov123_02299630(p, 0x10);
    }
}

void func_ov123_0229a278(UnkStruct_0229a278 *p, unsigned char val)
{
    unsigned char cur = p->unk_A4;
    if (cur != val) {
        if (cur != 0x22) {
            func_ov123_0229a2f8((char *) p, (unsigned char) cur, 4);
            func_0200467c(0xb);
        }
        p->unk_A4 = val;
        func_ov123_0229a2f8((char *) p, (unsigned char) p->unk_A4, 5);
    }
}

void func_ov123_0229a248(unsigned char *this, unsigned char val)
{
    func_ov123_0229a224((unsigned char *) this);
    this[0xA6] = val;
    this[0xA7] = 4;
    func_ov123_0229a2f8((char *) this, (unsigned char) this[0xA6], 5);
}

void func_ov123_0229a224(unsigned char *obj)
{
    func_ov123_0229a2f8((char *) obj, (unsigned char) obj[0xa6], 4);
    obj[0xa6] = 0x22;
    obj[0xa7] = 0;
}

void func_ov123_0229a1f4(struct UnkStruct_0229a1f4 *p)
{
    if (p->unk_A7 != 0) {
        p->unk_A7--;
        if (p->unk_A7 == 0) {
            func_ov123_0229a224((unsigned char *) p);
        }
    }
}

void func_ov123_0229a1e8(void *arg)
{
    func_02070b84((char *) arg + 0xb8);
}

void func_ov123_0229a180(int p0, int p1, int p2, int p3)
{
    int a;
    int b;
    unsigned short t;

    a = func_ov123_0229ae7c(p0, p1);
    b = func_ov123_0229ae74(p0, p2);
    t = data_ov123_0229cf20.field & ~0x18;
    t |= data_ov123_0229cea0[p3];
    data_ov123_0229cf20.field = t;
    func_020896b8(1, &data_ov123_0229cf20, a, b, -1, -1, 0);
}

void func_ov123_0229a148(int a0, int a1, int a2)
{
    int v1 = func_ov123_0229ae7c(a0, a1);
    int v2 = func_ov123_0229ae74(a0, a2);
    func_020896b8(1, (void *) (&data_ov123_0229cf08), v1, v2, -1, -1, 0);
}

void func_ov123_0229a0cc(int *p0, int p1, int p2)
{
    int res1, res2;
    unsigned char b;
    int *ptr;

    res1 = func_ov123_0229ae7c((int) p0, p1);
    res2 = func_ov123_0229ae74((int) p0, p2);
    b = ((unsigned char *) p0)[0xa4];
    ptr = data_ov123_0229cfec[b];
    if (func_ov123_02299650((void *) p0, 0x800) != 0) {
        ptr = data_ov123_0229ce90;
    }
    if (((unsigned char *) p0)[0xa4] == 1) {
        res1 -= 2;
        res2 -= 2;
    }
    if (ptr != 0) {
        func_02088df8(1, ptr, res1, res2, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}

int func_ov123_0229a094(void *arg0, void *arg1, void *arg2)
{
    int v1, v2;
    v1 = func_ov123_0229ae7c((int) arg0, (int) arg1);
    v2 = func_ov123_0229ae74((int) arg0, (int) arg2);
    return func_020896b8(1, &data_ov123_0229ceb0, v1, v2, -1, -1, 0);
}

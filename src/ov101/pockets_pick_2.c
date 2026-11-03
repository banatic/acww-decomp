/* pockets_pick_2: 5 functions, module ov101
 * mwccarm 1.2/base -O4,s
 * func_ov101_0229c7d0 @ 0x0229c7d0, 0x74 bytes, Thumb
 * func_ov101_0229c780 @ 0x0229c780, 0x50 bytes, Thumb
 * func_ov101_0229c720 @ 0x0229c720, 0x60 bytes, Thumb
 * func_ov101_0229c6d4 @ 0x0229c6d4, 0x4c bytes, Thumb
 * func_ov101_0229c6a0 @ 0x0229c6a0, 0x34 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0xb6 - 0x8d - 1];
    unsigned char unk_B6;
    unsigned char pad_B7[0x229c - 0xb6 - 1];
    unsigned char unk_229C[1];
} UnkStruct_0229c7d0;

extern int func_ov101_0229c2ac(void *, int);
extern int func_ov101_0229c878(UnkStruct_0229c7d0 *);
extern int func_ov101_0229c868(UnkStruct_0229c7d0 *);
extern void func_ov002_0220a05c(unsigned char *, int, int, int, int);
extern void func_ov101_0229c28c(UnkStruct_0229c7d0 *, int);
extern int func_ov002_02208ad8(void *, unsigned char);
extern int func_ov002_0220a08c(void *, void *, int, int);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern int func_ov002_022090e4(void *, int arg1);
extern int func_ov002_02208ae4(void *);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_0208e4c0(void *, int);
extern void func_ov002_0220a374(void *p, int val);

void func_ov101_0229c7d0(UnkStruct_0229c7d0 *p)
{
    int res1;
    int res2;
    if (func_ov101_0229c2ac(p, 4)) {
        res1 = func_ov101_0229c878(p);
        res2 = func_ov101_0229c868(p);
        func_ov002_0220a0b4((void *) p->unk_229C, res1, res2);
        func_ov101_0229c28c(p, 4);
    } else {
        res1 = func_ov101_0229c878(p);
        res2 = func_ov101_0229c868(p);
        func_ov002_0220a05c(p->unk_229C, res1, res2, 3, 1);
        p->unk_B6 = p->unk_8D;
        func_ov002_02208098((void *) p, 10);
    }
}

void func_ov101_0229c780(unsigned char *p)
{
    void *r4 = (void *) func_ov002_02208ae4(p + 0x2300);
    int r2 = func_ov002_02208ad8(p + 0x2300, *(unsigned char *) (p + 0xb8));
    func_ov002_0220a08c(p + 0x229c, r4, r2, 2);
    *(unsigned char *) (p + 0xb6) = *(unsigned char *) (p + 0x8d);
    func_ov002_02208098(p, 10);
}

void func_ov101_0229c720(void *p)
{
    unsigned char *base = (unsigned char *) p;
    int v1;
    int v2;
    base[0xb7] = 1;
    base[0xb8] = func_ov002_022090e4(base + 0x2300, 1);
    v1 = func_ov002_02208ae4(base + 0x2300);
    v2 = func_ov002_02208ad8(base + 0x2300, base[0xb8]);
    func_ov002_0220a0b4(base + 0x229c, v1, v2);
    func_0208e4c0(base + 0x229c, 8);
    func_ov002_02208098(p, 0x14);
}

void func_ov101_0229c6d4(unsigned char *self)
{
    int a, b;

    self[0xb8] = 0;
    a = func_ov002_02208ae4(self + 0x2300);
    b = func_ov002_02208ad8(self + 0x2300, self[0xb8]);
    func_ov002_0220a0b4(self + 0x229c, a, b);
    func_ov002_0220a374(self + 0x229c, 7);
}

void func_ov101_0229c6a0(char *self)
{
    int a = func_ov101_0229c878((UnkStruct_0229c7d0 *) self);
    int b = func_ov101_0229c868((UnkStruct_0229c7d0 *) self);
    func_ov002_0220a0b4((void *) (self + 0x229c), a, b);
    func_ov002_0220a374((void *) (self + 0x229c), 1);
}

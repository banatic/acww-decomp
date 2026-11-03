/* pockets_swap_3: 5 functions, module ov107
 * mwccarm 1.2/base -O4,s
 * func_ov107_0229ce1c @ 0x0229ce1c, 0x74 bytes, Thumb
 * func_ov107_0229cdcc @ 0x0229cdcc, 0x50 bytes, Thumb
 * func_ov107_0229cd68 @ 0x0229cd68, 0x64 bytes, Thumb
 * func_ov107_0229cd1c @ 0x0229cd1c, 0x4c bytes, Thumb
 * func_ov107_0229cce8 @ 0x0229cce8, 0x34 bytes, Thumb
 */

typedef struct {
    char pad_00[0xbc];
    unsigned char unk_BC;
    unsigned char unk_BD;
    char pad_BE[0x21f6];
    char unk_22B4[0x64];
    char unk_2318[1];
} UnkStruct_0229cd68;

extern int func_ov107_0229c2b4(int a, int b);
extern int func_ov107_0229cec4(int a);
extern int func_ov107_0229ceb4(int a);
extern void func_ov107_0229c294(int a, int b);
extern void func_ov002_0220a0b4(int a, int b, int c);
extern void func_ov002_0220a05c(int a, int b, int c, int d, int e);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov002_02208ad8(void *p, unsigned char b);
extern int func_ov002_0220a08c(void *p, void *a, int b, int c);
extern int func_ov002_022090e4(void *ptr, int a);
extern int func_ov002_02208ae4(void *ptr);
extern void func_0208e4c0(void *ptr, int a);
extern void func_ov002_0220a374(void *, int);

void func_ov107_0229ce1c(int r4)
{
    int r5;
    int r2;
    int r0;
    int r1;

    if (func_ov107_0229c2b4(r4, 4) != 0) {
        r5 = func_ov107_0229cec4(r4);
        r2 = func_ov107_0229ceb4(r4);
        func_ov002_0220a0b4(r4 + 0x22b4, r5, r2);
        func_ov107_0229c294(r4, 4);
    } else {
        r5 = func_ov107_0229cec4(r4);
        r2 = func_ov107_0229ceb4(r4);
        func_ov002_0220a05c(r4 + 0x22b4, r5, r2, 3, 1);
        r1 = *(unsigned char *) (r4 + 0x8d);
        *(unsigned char *) (r4 + 0xbb) = r1;
        func_ov002_02208098((void *) (r4), 8);
    }
}

void func_ov107_0229cdcc(unsigned char *obj)
{
    void *a = (void *) func_ov002_02208ae4(obj + 0x2318);
    int b = func_ov002_02208ad8(obj + 0x2318, obj[0xbd]);
    func_ov002_0220a08c(obj + 0x22b4, a, b, 2);
    obj[0xbb] = obj[0x8d];
    func_ov002_02208098((void *) (obj), 8);
}

void func_ov107_0229cd68(UnkStruct_0229cd68 *p)
{
    int v1, v2;
    p->unk_BC = 0x4;
    p->unk_BD = func_ov002_022090e4(p->unk_2318, 1);
    v1 = func_ov002_02208ae4(p->unk_2318);
    v2 = func_ov002_02208ad8(p->unk_2318, p->unk_BD);
    func_ov002_0220a0b4((int) p->unk_22B4, v1, v2);
    func_0208e4c0(p->unk_22B4, 8);
    func_ov002_02208098((void *) (p), 12);
}

void func_ov107_0229cd1c(unsigned char *self)
{
    int a, b;
    self[0xbd] = 0;
    a = func_ov002_02208ae4(self + 0x2318);
    b = func_ov002_02208ad8(self + 0x2318, self[0xbd]);
    func_ov002_0220a0b4((int) (self + 0x22b4), a, b);
    func_ov002_0220a374(self + 0x22b4, 7);
}

void func_ov107_0229cce8(int arg0)
{
    int local_0;
    int r4;
    int r5;
    int r2;

    r5 = arg0;
    r4 = func_ov107_0229cec4((int) ((void *) arg0));
    r2 = func_ov107_0229ceb4(r5);
    func_ov002_0220a0b4(r5 + 0x22b4, r4, r2);
    func_ov002_0220a374((void *) (r5 + 0x22b4), 1);
}

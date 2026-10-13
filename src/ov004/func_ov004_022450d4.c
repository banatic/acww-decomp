/* func_ov004_022450d4 @ 0x022450d4, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_022450d4 {
    char unk_00[0x178];
    Vec3 arm[2];
    char unk_190[0x196 - 0x190];
    unsigned char unk_196;
} UnkStruct_022450d4;

extern void func_02034270(void *w, Vec3 *v, int a, int b);
extern int func_020341c8(void *w, int a);
extern void func_0203423c(void *w);
extern int func_ov004_02244e38(UnkStruct_022450d4 *self, Vec3 *p);

int func_ov004_022450d4(UnkStruct_022450d4 *self)
{
    char w1[0x40];
    char w2[0x40];
    unsigned char n, kind;
    int d;
    Vec3 *q;

    kind = self->unk_196;
    n = 0;
    q = self->arm;
    func_02034270(w1, q, 0, 1);
    d = func_020341c8(w1, 1);
    func_0203423c(w1);
    if (d <= 0 || d > q->y || (kind == 0x1e && func_ov004_02244e38(self, q) != 0)) {
        n = n + 1;
    }
    func_02034270(w2, q + 1, 0, 1);
    d = func_020341c8(w2, 1);
    func_0203423c(w2);
    if (d <= 0 || d > q[1].y || (kind == 0x1e && func_ov004_02244e38(self, q + 1) != 0)) {
        n = n + 2;
    }
    return n;
}

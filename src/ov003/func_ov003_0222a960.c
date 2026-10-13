/* func_ov003_0222a960 @ 0x0222a960, 0xf0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off
typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    char pad_00[0x40];
    int unk_40;
    int unk_44;
    int unk_48;
    char pad_4C[0xa4 - 0x4c];
} UnkStruct_0222a960;

extern UnkStruct_0222a960 data_ov003_0225f4dc[];
extern void *data_020ccf94;
extern char *func_020961a8(int i);
extern int func_0200322c(void *a, void *b);
extern int func_0203162c(Vec3 *v, char *p, int ang, int a, int b, int c);
extern void func_ov003_0222a7bc(UnkStruct_0222a960 *e, int ang, int st);
extern int func_02073d90(void *h);
extern int func_02073918(void *h, int i);
extern void func_02073820(void *h);
extern void func_020737f0(void *h, char *b, int n);
extern void func_02073770(void *h, int a, int b);

int func_ov003_0222a960(int i, int flag)
{
    int st;
    int ang;
    char *p;
    char b;
    Vec3 v;
    UnkStruct_0222a960 *e;
    char *q;
    void *h;
    if (i < 0 || i > 3) {
        return 0;
    }
    p = func_020961a8(i);
    if (p == 0) {
        return 0;
    }
    p += 0x5c;
    e = &data_ov003_0225f4dc[i];
    st = *(int *) ((char *) e + 0x90);
    if (st == 0x38 || st == 0x39 || st == 0x3a) {
        if (flag) {
            return 1;
        }
        e->unk_40 = 4;
        return 1;
    }
    q = (char *) e + 0x60;
    ang = func_0200322c((char *) e + 0x6c, q);
    if (func_0203162c(&v, p, ang, 0x7800, 0x2000, 0xc)) {
        *(int *) q = v.x;
        *(int *) (q + 4) = v.y;
        *(int *) (q + 8) = v.z;
    }
    func_ov003_0222a7bc(e, ang, st);
    if (flag) {
        e->unk_40 = 1;
    }
    e->unk_48 = 3;
    h = data_020ccf94;
    if (func_02073d90(h) && func_02073918(h, i)) {
        b = 2;
        h = data_020ccf94;
        func_02073820(h);
        func_020737f0(h, &b, 1);
        func_02073770(h, 0x2a, 4);
    }
    return 1;
}

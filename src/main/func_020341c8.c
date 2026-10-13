/* func_020341c8 @ 0x020341c8, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    unsigned char pad_00[0x10];
    Vec3 pos;
    int unk_1C;
    int unk_20;
    unsigned char pad_24[0x14];
    int unk_38;
} UnkStruct_020341c8;

extern int func_02031078(int a0, int a1, int *o1, int *o2, int *o3);
extern long long func_020ea940(Vec3 *a, Vec3 *b);
extern int FX_MulFunc(int a, int b);

int func_020341c8(UnkStruct_020341c8 *o, int flag)
{
    int a, b, c, t, pz;
    Vec3 v;
    long long d;

    if (flag == 0) {
        return o->unk_38;
    }
    if (func_02031078(o->unk_1C, o->unk_20, &a, &b, &c) != 0 && c != 2) {
        pz = o->unk_20;
        v.x = (o->unk_1C << 13) + 0x1000;
        v.y = 0;
        v.z = (pz << 13) + 0x1000;
        t = a;
        d = func_020ea940(&v, &o->pos);
        if ((long long) FX_MulFunc(t, t) >= d) {
            return o->unk_38 + b;
        }
    }
    return o->unk_38;
}

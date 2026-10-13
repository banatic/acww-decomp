/* func_0202fe00 @ 0x0202fe00, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    int pad_00[10];
    int unk_28;
    int unk_2C;
    int unk_30;
} UnkStruct_0202fe00;

extern int func_0202fb28(UnkStruct_0202fe00 *o, Vec *v);
extern int func_0202f9d0(UnkStruct_0202fe00 *o, Vec *out, Vec *a, Vec *b);
extern int FX_MulFunc(int a, int b);

int func_0202fe00(UnkStruct_0202fe00 *o, Vec *a, Vec *b, int t)
{
    Vec d;
    int ok;

    ok = 0;
    if (func_0202fb28(o, a) <= 0 && func_0202fb28(o, b) > 0 && func_0202f9d0(o, &d, a, b)) {
        a->x = d.x + FX_MulFunc(t, o->unk_28);
        a->y = d.y + FX_MulFunc(t, o->unk_2C);
        a->z = d.z + FX_MulFunc(t, o->unk_30);
        ok = 1;
    }
    return ok;
}

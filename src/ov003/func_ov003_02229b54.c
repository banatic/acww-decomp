/* func_ov003_02229b54 @ 0x02229b54, 0xb0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int m[9];
    Vec3 t;
} Mtx43;
typedef struct {
    char pad_00[0x40];
    int unk_40;
    int pad_44[2];
    int unk_4C;
    int unk_50;
    Vec3 unk_54;
    Vec3 unk_60;
} UnkStruct_02229b54;
extern int func_02096190(unsigned idx);
extern void func_0209549c(Mtx43 *out, unsigned idx);
extern void func_ov003_02219668(Mtx43 *m, Vec3 *s);
extern int func_0203f7d0(Vec3 *d, Vec3 *s);
extern void func_0205fbc4(Vec3 *a, Vec3 *b, int *c, int *d, int e);
int func_ov003_02229b54(UnkStruct_02229b54 *o, unsigned idx)
{
    volatile Vec3 c;
    Mtx43 m;
    Vec3 s;
    Vec3 v;
    Mtx43 t;
    Vec3 a;
    Vec3 b;
    if (idx >= 4) {
        o->unk_40 = 4;
        return 0;
    }
    if (!func_02096190(idx)) {
        o->unk_40 = 4;
        return 0;
    }
    func_0209549c(&t, idx);
    m = t;
    s.x = 0x800;
    s.y = 0;
    s.z = 0;
    func_ov003_02219668(&m, &s);
    v.x = m.t.x;
    v.y = m.t.y;
    v.z = m.t.z;
    func_0203f7d0(&v, &v);
    c.x = v.x;
    c.y = v.y;
    c.z = v.z;
    a.x = v.x;
    a.y = v.y;
    a.z = v.z;
    b.x = o->unk_60.x;
    b.y = o->unk_60.y;
    b.z = o->unk_60.z;
    func_0205fbc4(&a, &b, &o->unk_4C, &o->unk_50, 3);
    o->unk_54.x = o->unk_60.x;
    o->unk_54.y = o->unk_60.y;
    o->unk_54.z = o->unk_60.z;
    return 1;
}

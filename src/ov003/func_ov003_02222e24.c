/* func_ov003_02222e24 @ 0x02222e24, 0xe8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02045bb8(unsigned char a, int b);
extern void func_0204f794(int *out, int a, int b);
extern int func_ov003_02223078(int p1, void *v);
extern void *func_02045bac(int id);
extern void func_ov003_022210d4(int p1, unsigned short h, void *pa, void *w, int a, int b);
extern void func_ov003_02221094(int p1, unsigned short h, void *pa, void *w, int a);

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int a, b;
} Pair;
typedef struct {
    char pad_00[8];
    unsigned short unk_08;
    unsigned short unk_0A;
} UnkStruct_02222e24;

extern Vec3 *data_ov003_02239f5c[2];

typedef struct {
    unsigned short unk_00;
} UnkStruct_02222e24_2;

void func_ov003_02222e24(UnkStruct_02222e24_2 *self, int p1, int *p2)
{
    int id;
    int flag;
    volatile unsigned short cc[3];
    Pair pa;
    Pair pb;
    struct {
        Vec3 a;
        Vec3 b;
    } o;
    Vec3 wa;
    Vec3 wb;
    Vec3 *e;
    UnkStruct_02222e24 *r;
    unsigned int ok;
    unsigned short h;
    int h1, h2;
    unsigned short tv;

    id = func_02045bb8((unsigned char) p1, 0);
    if (id < 0) {
        return;
    }
    ok = 0;
    flag = 0;
    h = self->unk_00;
    if (h >= 0x66 && h <= 0x68) {
        ok = 1;
    }
    if (ok > 0) {
        e = data_ov003_02239f5c[0];
        if (h == 0x66) {
            flag = 1;
        }
    } else if (h >= 0x6a && h <= 0x6c) {
        e = data_ov003_02239f5c[1];
        if (h == 0x6a) {
            flag = 1;
        }
    }
    func_0204f794(&o.a.x, p2[0], p2[1]);
    e = e + func_ov003_02223078(p1, &o.a);
    r = (UnkStruct_02222e24 *) func_02045bac(id);
    o.b.x = o.a.x + e->x;
    o.b.y = o.a.y + e->y;
    o.b.z = o.a.z + e->z;
    cc[2] = r->unk_08;
    tv = cc[2];
    cc[1] = tv;
    cc[0] = tv;
    h1 = cc[0] >> 8;
    h2 = cc[1] & 0xff;
    if (flag == 0) {
        wa.x = o.b.x;
        wa.y = o.b.y;
        wa.z = o.b.z;
        pa.a = h1;
        pa.b = h2;
        func_ov003_022210d4(p1, r->unk_0A, &pa, &wa, 0, 0);
    } else {
        wb.x = o.b.x;
        wb.y = o.b.y;
        wb.z = o.b.z;
        pb.a = h1;
        pb.b = h2;
        func_ov003_02221094(p1, r->unk_0A, &pb, &wb, 0);
    }
}

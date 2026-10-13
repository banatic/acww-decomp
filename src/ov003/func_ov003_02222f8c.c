/* func_ov003_02222f8c @ 0x02222f8c, 0xec bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f794(int *out, int a, int b);
extern int func_0204b710(void *self);
extern int func_02045bb8(unsigned char a, unsigned char b);
extern void *func_02045bac(int id);
extern void func_0204f818(int *a, int *b, void *v);
extern void func_ov003_022210d4(int p1, unsigned short h, void *pa, void *w, int a, int b);

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int a, b;
} Pair;
typedef struct {
    char pad_00[8];
    unsigned short unk_08;
} UnkStruct_02222f8c;

extern Vec3 *data_ov003_02239f5c[3];
extern unsigned short data_ov003_02236688[];

typedef struct {
    unsigned short unk_00;
} UnkStruct_02222f8c_2;

void func_ov003_02222f8c(UnkStruct_02222f8c_2 *self, int p1, int *p2)
{
    Vec3 *e;
    int i, n;
    int flag;
    volatile unsigned short cc[3];
    Pair pa;
    Pair pa2;
    Vec3 out;
    Vec3 w;
    Vec3 w2;
    UnkStruct_02222f8c *r;
    unsigned short k;
    unsigned short h;
    unsigned short tv;
    int id;

    func_0204f794(&out.x, p2[0], p2[1]);
    h = self->unk_00;
    switch (h) {
        case 0xcc:
            e = data_ov003_02239f5c[2];
            n = 2;
            k = 0x1548;
            break;
        case 0x5b:
            e = data_ov003_02239f5c[0];
            n = 3;
            k = 0x14b8;
            break;
        default:
            e = data_ov003_02239f5c[0];
            n = 3;
            k = data_ov003_02236688[func_0204b710(self)];
            break;
    }
    pa.a = 0;
    pa.b = 0;
    for (i = 0; i < n; i++) {
        id = func_02045bb8((unsigned char) p1, (unsigned char) i);
        w.x = out.x + e->x;
        w.y = out.y + e->y;
        w.z = out.z + e->z;
        if (id >= 0) {
            r = (UnkStruct_02222f8c *) func_02045bac(id);
            cc[2] = r->unk_08;
            tv = cc[2];
            cc[1] = tv;
            cc[0] = tv;
            pa.a = cc[0] >> 8;
            pa.b = cc[1] & 0xff;
            flag = 0;
        } else {
            func_0204f818(&pa.a, &pa.b, &w);
            flag = 1;
        }
        w2.x = w.x;
        w2.y = w.y;
        w2.z = w.z;
        pa2.a = pa.a;
        pa2.b = pa.b;
        func_ov003_022210d4(p1, k, &pa2, &w2, flag, i);
        e++;
    }
}

/* func_ov003_0221efec @ 0x0221efec, 0xca bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0221efa4(void *p);
extern void *func_ov003_0221f0b8(void *p, int a, int b);
extern int func_02037544(void *argument0);
extern int func_020ea990(void *v, void *pos);
extern int func_ov003_0221efc4(void *p, int d, void *v, int kind);

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int kind;
    int unk_04;
    int unk_08;
} UnkStruct_0221efec;

extern void func_02037514(UnkStruct_0221efec *out, const unsigned char *c, int k);

void *func_ov003_0221efec(void *p, Vec3 *pos)
{
    int i, j;
    unsigned int k;
    void *c;
    unsigned int n;
    int gx, gz;
    int wz0, zi;
    int xj;
    volatile Vec3 base;
    UnkStruct_0221efec e;
    Vec3 v;
    UnkStruct_0221efec tmp;
    int d;

    func_ov003_0221efa4(p);
    gx = pos->x >> 17;
    gz = pos->z >> 17;
    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            wz0 = (gz + i) << 17;
            zi = gz + i;
            xj = gx + j;
            base.x = xj << 17;
            base.z = wz0;
            c = func_ov003_0221f0b8(p, xj, zi);
            if (c != 0) {
                n = func_02037544(c);
                for (k = 0; k < n; k++) {
                    func_02037514(&tmp, c, k);
                    e = tmp;
                    switch (e.kind) {
                        case 5:
                        case 0xf:
                        case 0x11:
                        case 0x12:
                            v.x = base.x + e.unk_04;
                            v.y = 0;
                            v.z = base.z + e.unk_08;
                            d = func_020ea990(&v, pos);
                            func_ov003_0221efc4(p, d, &v, e.kind);
                            break;
                    }
                }
            }
        }
    }
    return p;
}

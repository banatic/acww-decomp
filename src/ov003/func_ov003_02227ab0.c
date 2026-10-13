/* func_ov003_02227ab0 @ 0x02227ab0, 0x23c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    char pad_00[0x208];
    int a, b;
    char pad_210[0x24c - 0x210];
} UnkStruct_02227ab0;
typedef struct {
    signed char x, y;
} Pt;

extern int data_021c67a4;
extern Vec3 data_021c67d0;
extern UnkStruct_02227ab0 data_ov003_0225f76c[];
extern UnkStruct_02227ab0 data_ov003_0225fe50[];

extern void func_0204f7e0(Vec3 *d, Vec3 *s);
extern void func_0204f794(Vec3 *d, int x, int z);
extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern int func_02031b5c(int x, int z);
extern int func_02031ba0(int x, int z);
extern int func_ov003_02227cec(void *self, Pt *out, int *n, unsigned kind);
extern int func_ov003_0222793c(int a, int b);
extern int func_ov003_0222799c(Vec3 *a, Vec3 *b, int dx, int dz, int dz2);

int func_ov003_02227ab0(void *self, int *px, int *pz, int *ox, int *oz, unsigned kind, int mode, UnkStruct_02227ab0 *skip)
{
    UnkStruct_02227ab0 *q;
    int n;
    Pt tiles[16];
    int bx;
    Vec3 d;
    Vec3 v50;
    int cnt;
    int z;
    unsigned kk;
    int iend;
    int jend;
    int by;
    int lo;
    int k;
    int m;
    int *pp;
    int x;
    int i;
    int t;
    int j;
    Vec3 v5c;
    int hi;
    Pt pts[258];

    kk = kind;
    cnt = 0;
    n = 0;
    if (data_021c67a4 == 0) {
        return cnt;
    }
    d.x = data_021c67d0.x;
    d.y = data_021c67d0.y;
    d.z = data_021c67d0.z;
    func_0204f7e0(&v50, &d);
    if (func_ov003_02227cec(self, tiles, &n, kk) == 0) {
        return cnt;
    }
    m = func_ov003_0222793c(0, (unsigned short) n);
    *ox = tiles[m].x;
    *oz = tiles[m].y;
    x = *ox;
    z = *oz;
    if (mode == 0) {
        q = data_ov003_0225f76c;
        for (k = 0; k < 3; k++) {
            if (skip != q) {
                pp = &q->a;
                if (x == q->a && z == pp[1]) {
                    return 0;
                }
            }
            q++;
        }
    } else if (mode == 1) {
        q = data_ov003_0225fe50;
        for (k = 3; k < 6; k++) {
            if (skip != q) {
                pp = &q->a;
                if (x == q->a && z == pp[1]) {
                    return 0;
                }
            }
            q++;
        }
    }
    func_0204f800(&lo, &hi, x, z, 0, 0);
    t = lo;
    iend = t + 0x10;
    jend = hi + 0x10;
    for (i = lo; i < iend; i++) {
        for (j = hi; j < jend; j++) {
            switch (kk) {
                case 5:
                case 6:
                    if (func_02031b5c(i, j) == 1) {
                        pts[cnt].x = (signed char) i;
                        pts[cnt].y = (signed char) j;
                        cnt++;
                    }
                    break;
                case 0:
                case 1:
                    if (func_02031b5c(i, j) == 2) {
                        pts[cnt].x = (signed char) i;
                        pts[cnt].y = (signed char) j;
                        cnt++;
                    }
                    break;
                case 2:
                    if (j < hi + 3 && func_02031b5c(i, j) == 2) {
                        pts[cnt].x = (signed char) i;
                        pts[cnt].y = (signed char) j;
                        cnt++;
                    }
                    break;
                case 3:
                    if (func_02031ba0(i, j) != 0) {
                        pts[cnt].x = (signed char) i;
                        pts[cnt].y = (signed char) j;
                        cnt++;
                    }
                    break;
                case 4:
                    if (func_02031b5c(i, j) == 2 || func_02031b5c(i, j) == 1) {
                        pts[cnt].x = (signed char) i;
                        pts[cnt].y = (signed char) j;
                        cnt++;
                    }
                    break;
            }
        }
    }
    if (cnt == 0) {
        *px = -1;
        *pz = -1;
        return 0;
    }
    m = func_ov003_0222793c(0, (unsigned short) cnt);
    by = pts[(short) m].y;
    bx = pts[(short) m].x;
    func_0204f794(&v5c, bx, by);
    if (func_ov003_0222799c(&v5c, &v50, 0xa000, 0x10000, 0xa000) != 0) {
        *px = -1;
        *pz = -1;
        return 0;
    }
    *px = bx;
    *pz = by;
    return 1;
}

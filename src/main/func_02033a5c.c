/* func_02033a5c @ 0x02033a5c, 0x1d0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} UnkStruct_02033a5c;

typedef struct {
    int unk_00, unk_04, unk_08, unk_0C;
    unsigned char unk_10, unk_11, unk_12, unk_13;
    unsigned char unk_14;
} UnkStruct_02033a5c_2;

typedef struct {
    char pad_00[0x15];
    unsigned char unk_15;
    char pad_16[0x1e - 0x16];
} UnkStruct_02033a5c_3;

extern UnkStruct_02033a5c_3 data_020c907c[];
extern int data_021c317c;
extern UnkStruct_02033a5c_2 *func_020342c0(void *a, int x, int y);
extern int func_02033a24(void *a0, UnkStruct_02033a5c *p1, UnkStruct_02033a5c *p2, UnkStruct_02033a5c *p3, void *t, int k,
                         int z);

static inline void setv(UnkStruct_02033a5c *d, int x, int y, int z)
{
    d->x = x;
    d->y = y;
    d->z = z;
}
static inline void setv0(UnkStruct_02033a5c *d, UnkStruct_02033a5c *s, int y)
{
    d->x = s->x;
    d->y = y;
    d->z = s->z;
}

void func_02033a5c(void *a0, void *a1, int x0, int x1, int y0, int y1)
{
    UnkStruct_02033a5c v[17];
    int y;
    int f;
    int t;
    UnkStruct_02033a5c_2 *e;
    int x1a;
    int x0a;
    int x;
    int z1;
    int z0;
    int T;

    for (y = y0; y <= y1; y++) {
        x = x0;
        T = (y << 13) + 0x1000;
        for (; x <= x1; x++) {
            e = func_020342c0(a1, x, y);
            if (e == 0) {
                continue;
            }
            v[0].x = (x << 13) + 0x1000;
            v[0].y = 0;
            v[0].z = T;
            x1a = v[0].x + 0x1000;
            x0a = v[0].x - 0x1000;
            z1 = T + 0x1000;
            z0 = T - 0x1000;
            t = e->unk_14;
            if (t < 0x7c) {
                f = data_020c907c[t].unk_15;
            } else {
                f = 0;
            }
            if (f != 0) {
                setv(&v[1], x0a, e->unk_00, z0);
                setv(&v[2], x0a, e->unk_00, z1);
                setv(&v[3], x1a, e->unk_00, z1);
                setv(&v[4], x1a, e->unk_00, z0);
                func_02033a24(a0, &v[1], &v[2], &v[3], &data_021c317c, e->unk_10, 0);
                func_02033a24(a0, &v[1], &v[3], &v[4], &data_021c317c, e->unk_10, 0);
            } else {
                setv(&v[5], v[0].x, e->unk_00, T);
                setv(&v[6], x1a, e->unk_00, z0);
                setv(&v[7], x0a, e->unk_00, z0);
                func_02033a24(a0, &v[5], &v[6], &v[7], &data_021c317c, e->unk_10, 0);
                setv0(&v[8], &v[0], e->unk_04);
                setv(&v[9], x0a, e->unk_04, z0);
                setv(&v[10], x0a, e->unk_04, z1);
                func_02033a24(a0, &v[8], &v[9], &v[10], &data_021c317c, e->unk_11, 0);
                setv0(&v[11], &v[0], e->unk_08);
                setv(&v[12], x0a, e->unk_08, z1);
                setv(&v[13], x1a, e->unk_08, z1);
                func_02033a24(a0, &v[11], &v[12], &v[13], &data_021c317c, e->unk_12, 0);
                setv0(&v[14], &v[0], e->unk_0C);
                setv(&v[15], x1a, e->unk_0C, z1);
                setv(&v[16], x1a, e->unk_0C, z0);
                func_02033a24(a0, &v[14], &v[15], &v[16], &data_021c317c, e->unk_13, 0);
            }
        }
    }
}

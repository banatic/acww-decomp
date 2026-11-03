/* path_walker_8: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020134f8 @ 0x020134f8, 0x1e bytes, Thumb
 * func_02013450 @ 0x02013450, 0xa8 bytes, Thumb
 * func_02013440 @ 0x02013440, 0x10 bytes, Thumb
 * func_02013420 @ 0x02013420, 0x20 bytes, Thumb
 * func_020133b4 @ 0x020133b4, 0x6a bytes, Thumb
 */

typedef struct {
    int x, y;
} Pt;

typedef struct {
    unsigned int x, y;
} UPt;

typedef struct {
    unsigned char lo : 4;
    unsigned char hi : 4;
} NibblePair;

extern const Pt data_021c172c[4];
extern int func_020131c0(void *a, int dir);
extern int func_0204ed58(void *map, unsigned int x, unsigned int y);
extern void MI_CpuFill8(void *ptr, int value, int count);
extern void MI_CpuCopy8(void *dst, const void *src, unsigned int n);

int func_020134f8(int unused, int mask)
{
    int i;

    if (mask != 0) {
        for (i = 0; i < 4; i++) {
            if (((mask >> i) & 1) != 0) {
                return i;
            }
        }
    }
    return 4;
}

int func_02013450(void *a, UPt *out, UPt *pos, int dir, UPt *limit, void *map)
{
    int mask, dx, dy;
    int i, t, r;
    unsigned int nx, ny;

    t = func_020134f8((int) a, dir);
    if (t < 4) {
        dx = data_021c172c[t].x;
        dy = data_021c172c[t].y;
        mask = ~(dir | func_020131c0(a, dir));
        i = 0;
        while (pos->x < limit->x && pos->y < limit->y) {
            pos->x += dx;
            pos->y += dy;
            i++;
            r = func_0204ed58(map, pos->x, pos->y);
            if (r == 0) {
                nx = pos->x - dx;
                ny = pos->y - dy;
                out->x = nx;
                out->y = ny;
                return -(i - 1);
            }
            if (r & mask) {
                out->x = pos->x;
                out->y = pos->y;
                return i;
            }
        }
    }
    return 0;
}

void func_02013440(void *ptr)
{
    MI_CpuFill8((char *) ptr + 0x2c, 0, 0x5a);
}

int func_02013420(unsigned char *p)
{
    int i;
    p += 0x2c;
    for (i = 0; i < 29; i++) {
        if (((unsigned int) (p[2]) << 24) >> 28 == 0) {
            return i;
        }
        p += 3;
    }
    return 29;
}

void func_020133b4(void *obj, int p1, int p2, void *data)
{
    int count;
    unsigned char *p;
    NibblePair *np;

    count = func_02013420((unsigned char *) obj);
    p = (unsigned char *) obj + 0x2c + 3 * count;
    while (count > 0) {
        MI_CpuCopy8(p - 3, p, 3);
        p -= 3;
        count--;
    }

    p1 &= 0xf;
    p2 &= 0xf;
    np = (NibblePair *) &p[2];
    np->hi = p1;
    np->lo = p2;
    p[0] = (unsigned char) ((int *) data)[0];
    p[1] = (unsigned char) ((int *) data)[1];
}

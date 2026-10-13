/* func_02013450 @ 0x02013450, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y;
} Pt;
typedef struct {
    unsigned int x, y;
} UPt;

extern const Pt data_021c172c[4];

extern int func_020134f8(void *a, int dir);
extern int func_020131c0(void *a, int dir);
extern int func_0204ed58(void *map, unsigned int x, unsigned int y);

int func_02013450(void *a, UPt *out, UPt *pos, int dir, UPt *limit, void *map)
{
    int mask, dx, dy;
    int i, t, r;
    unsigned int nx, ny;

    t = func_020134f8(a, dir);
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

/* func_ov068_0226c170 @ 0x0226c170, 0x6c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y;
} UnkStruct_0226c170;
typedef struct {
    unsigned short id;
} UnkStruct_0226c170_2;

extern void *data_021c80bc; // 0x021c80bc
extern UnkStruct_0226c170_2 *func_0204f5e0(void *, int, int, int, int, int);
extern int func_0204f294(void *, int, int);

int func_ov068_0226c170(void *unused, UnkStruct_0226c170 *p)
{
    void *g = data_021c80bc;
    UnkStruct_0226c170_2 *e;
    unsigned int ok;
    int r;
    int x, y, hx, hy;
    if (g != 0) {
        x = p->x;
        y = p->y;
        hx = x >> 4;
        hy = y >> 4;
        e = func_0204f5e0(g, hx, hy, x - (hx << 4), y - (hy << 4), 0);
        if (e != 0) {
            r = 0;
            ok = 0;
            if (e->id >= 0x1566 && e->id <= 0x1566) {
                ok = 1;
            }
            if (ok != 0) {
                if (func_0204f294(g, p->x, p->y) != 0) {
                    r = 1;
                }
            }
            return r;
        }
    }
    return 0;
}

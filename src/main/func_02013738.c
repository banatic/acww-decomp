/* func_02013738 @ 0x02013738, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y;
} Pt;

extern void func_0204f828(Pt *, Pt *, int);
extern void func_0204f800(char *, char *, int, int, int, int);
extern int func_02078ec0(int, int, int);
extern int func_0207cc54(int, int, int);
extern void func_0204f7ac(int, int, int, int, int);

struct UnkStruct_02013738 {
    int dx, dy;
};
extern struct UnkStruct_02013738 data_021c172c[];

int func_02013738(int unused, int p1, int p2)
{
    Pt p, q, r;
    int mask, cnt, i, k;
    unsigned int nx, ny;

    mask = 0;
    p.x = 0;
    p.y = 0;
    q.x = 0;
    q.y = 0;
    r.x = 0;
    r.y = 0;
    cnt = 0;
    func_0204f828(&p, &q, p1);
    for (i = 0; i < 4; i++) {
        nx = q.x + data_021c172c[i].dx;
        ny = q.y + data_021c172c[i].dy;
        if (nx < 0x10 && ny < 0x10) {
            func_0204f800((char *) &r.x, (char *) &r.y, p.x, p.y, nx, ny);
            if (func_02078ec0(r.x, r.y, p2) != 0) {
                mask = (unsigned char) (mask | (1 << i));
                cnt++;
            }
        }
    }
    k = func_0207cc54(mask, cnt, 4);
    if ((unsigned int) k < 4) {
        func_0204f7ac(p1, p.x, p.y, q.x + data_021c172c[k].dx, q.y + data_021c172c[k].dy);
        return k;
    }
    return 4;
}

/* func_ov098_022a2bfc @ 0x022a2bfc, 0xdc bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y;
} Pt;

extern void *func_020984e8(void);
extern unsigned short *func_02099728(void *);
extern char *func_020961a8(int);
extern void *func_0204e414(void);
extern void func_0204f818(int *, int *, void *);
extern Pt *func_ov098_022a2cd8(void *, short);
extern unsigned short *func_0204f5e0(void *, int, int, int, int, int);
extern const short data_ov098_022a3240[];

int func_ov098_022a2bfc(void *obj)
{
    void *h2;
    int zA;
    int zB;
    int a;
    int b;
    char *st;
    unsigned int hit;
    unsigned short id;
    int i;
    int sx, sy;
    int base;
    int qx, qy;
    unsigned short *ip;
    Pt *p;
    unsigned short *r;

    ip = func_02099728(func_020984e8());
    hit = 0;
    id = *ip;
    if (id >= 0x1369 && id <= 0x1369) {
        hit = 1;
    }
    if (hit == 0 && !(id >= 0x136a && id <= 0x136a)) {
        return 0;
    }

    st = func_020961a8(4);
    a = 0;
    b = 0;
    h2 = func_0204e414();
    func_0204f818(&a, &b, st + 0x5c);
    i = 0;
    base = *(short *) (st + 0x8e);
    zB = 0;
    zA = 0;
    for (; i < 3; i++) {
        p = func_ov098_022a2cd8(obj, (short) (base + data_ov098_022a3240[i]));
        sx = a + p->x;
        sy = b + p->y;
        qx = sx >> 4;
        qy = sy >> 4;
        r = func_0204f5e0(h2, qx, qy, sx - (qx << 4), sy - (qy << 4), zA);
        if (r != 0) {
            hit = zB;
            if (*r >= 0xfc && *r <= 0xfd) {
                hit = 1;
            }
            if (hit != 0) {
                *(int *) ((char *) obj + 0x2e20) = sx;
                *(int *) ((char *) obj + 0x2e24) = sy;
                return 1;
            }
        }
    }
    return 0;
}

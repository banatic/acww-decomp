/* func_ov003_0222378c @ 0x0222378c, 0xe4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y;
} XY;

typedef struct {
    int unk_00;
    int unk_04;
    XY xy;
    int unk_10;
    int unk_14;
} UnkStruct_0222378c;

typedef struct {
    int unk_00;
    char pad_04[0xd4 - 4];
    int unk_D4;
} UnkStruct_0222378c_2;

extern int func_0204e414(void *a);
extern void func_ov003_02222af0(UnkStruct_0222378c *b);
extern void *func_0204f5e0(int h, int a, int c, int d, int e, int f);
extern int func_0204b7a0(void *h, int a);
extern UnkStruct_0222378c_2 *func_ov003_02223870(void *a, void *h, int n, int w);
extern void func_ov003_02222cac(UnkStruct_0222378c_2 *q, int a, int *pair, int c, int d, int e);

void func_ov003_0222378c(void *a, UnkStruct_0222378c *b)
{
    int pair[2];
    void *h;
    UnkStruct_0222378c_2 *q;
    int n;
    int w;
    int x, y, xh, yh;
    int x2, y2, f10;
    int f14;
    int r;
    XY *p;

    r = func_0204e414(a);
    if (r == 0) {
        func_ov003_02222af0(b);
        return;
    }
    p = &b->xy;
    x = p->x;
    y = p->y;
    xh = x >> 4;
    yh = y >> 4;
    h = func_0204f5e0(r, xh, yh, x - (xh << 4), y - (yh << 4), 0);
    if (h == 0) {
        func_ov003_02222af0(b);
        return;
    }
    p = &b->xy;
    x2 = p->x;
    y2 = p->y;
    f10 = b->unk_10;
    n = func_0204b7a0(h, f10);
    if (n <= 0 || n > 4) {
        func_ov003_02222af0(b);
        return;
    }
    {
        q = func_ov003_02223870(a, h, n - 1, (x2 ^ y2) & 1);
        if (q == 0) {
            func_ov003_02222af0(b);
            return;
        }
        if (q->unk_00 == 1) {
            switch (q->unk_D4) {
                case 4:
                case 5:
                case 6:
                case 7:
                    func_ov003_02222af0(b);
                    return;
            }
        }
        f14 = b->unk_14;
        pair[0] = x2;
        pair[1] = y2;
        func_ov003_02222cac(q, b->unk_04, pair, f10, n - 1, f14);
        b->unk_00 = 0;
    }
}

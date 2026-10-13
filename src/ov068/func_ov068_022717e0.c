/* func_ov068_022717e0 @ 0x022717e0, 0x13c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O1,s
 */

extern void *data_021c80bc;
extern int func_020ea990(void *a, void *b);
extern void func_0204f818(int *px, int *pz, void *p);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_0200322c(void *a, void *b);
extern void func_ov003_0223597c(int *out, int ang);
extern int FX_MulFunc(int a, int b);

void func_ov068_022717e0(char *self)
{
    int dist;
    char *p1e0;
    void *ctx;
    int xx;
    int zz;
    int ang;
    int score;
    int x, z;
    int v3[3];
    int *p204;
    unsigned char cnt;
    unsigned short *o;
    unsigned short v;
    int cx, cz;
    int lim;

    p204 = (int *) (self + 0x204);
    p1e0 = self + 0x1e0;
    ctx = data_021c80bc;
    score = 0;
    x = 0;
    z = 0;
    dist = func_020ea990(p204, p1e0);
    cnt = 0;
    func_0204f818(&x, &z, p1e0);
    xx = x;
    zz = z;
    cx = xx >> 4;
    cz = zz >> 4;
    o = func_0204f5e0(ctx, cx, cz, xx - (cx << 4), zz - (cz << 4), 0);
    if (o != 0) {
        v = *o;
        if (v == 0x500a) {
            score = 0x27ae;
        } else if (v >= 0xe3 && v <= 0xe7) {
            score = 0x191f;
        }
    }
    if (score > 0 && *(unsigned char *) (self + 0x24a) == 0) {
        if (dist > 0x266) {
            ang = func_0200322c(p204, p1e0);
            func_ov003_0223597c(&v3[0], ang);
            *(short *) (self + 0x23a) = ang;
            p204[0] = p204[0] + FX_MulFunc(v3[0], 0xa000);
            p204[2] = p204[2] + FX_MulFunc(v3[2], 0xa000);
        } else {
            cnt++;
        }
        lim = p204[1] - 0x19a;
        if (score < lim) {
            p204[1] = p204[1] - 0xcd;
        } else {
            cnt++;
        }
        if (cnt >= 2) {
            *(unsigned char *) (self + 0x251) = 0x13;
        }
    } else {
        *(int *) (self + 0x21c) = *(int *) (self + 0x21c) & 0xff0f;
        *(unsigned char *) (self + 0x251) = 0x13;
    }
}

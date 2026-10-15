/* func_020b289c @ 0x020b289c, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern int data_021f69b8;
extern void *data_021c80bc;

struct Entry {
    unsigned char b[10];
};
extern struct Entry data_020d1f24[];

struct Iter {
    int a;
    int b;
    int c;
};

extern int func_020b6660(void);
extern int func_020b22b8(void);
extern int func_020b5e10(void);
extern int func_020b64d4(int *p);
extern int func_020b64cc(int *p);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_020b2a68(struct Iter *it, struct Entry *e);
extern int func_020b2a20(struct Iter *it, int x, int z);
extern void func_020b2a64(struct Iter *it);

int func_020b289c(void)
{
    struct Iter it;
    void *ctx;
    unsigned short *o;
    unsigned int v;
    unsigned int n;
    int x;
    int z;
    int cx;
    int cz;
    int ok;
    unsigned int uok;
    int ok2;
    int ret;
    struct Entry *e;

    if (func_020b6660() == 0 || func_020b22b8() != 0) {
        return 0;
    }
    uok = (data_020e54a8 != 0) ? 0 : 1;
    if (uok == 0) {
        goto fail;
    }
    func_020b5e10();
    x = func_020b64d4(&data_021f69b8);
    func_020b5e10();
    z = func_020b64cc(&data_021f69b8);
    ctx = data_021c80bc;
    if (ctx == 0) {
        goto fail;
    }
    cx = x >> 4;
    cz = z >> 4;
    o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), 0);
    if (o == 0) {
        goto fail;
    }
    ok2 = 0;
    v = *o;
    if (v >= 0x5000 && v <= 0x5021) {
        ok2 = 1;
    }
    if (ok2 == 0) {
        goto fail;
    }
    if (v >= 0x5000 && v <= 0x5021) {
        n = v & 0xfff;
    } else {
        n = ~0u;
    }
    if (n < 0x22) {
        e = &data_020d1f24[n];
    } else {
        e = &data_020d1f24[0];
    }
    func_020b2a68(&it, e);
    ret = func_020b2a20(&it, x, z);
    func_020b2a64(&it);
    return ret;
fail:
    return 0;
}

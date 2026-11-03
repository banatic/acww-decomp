/* town_posts: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b3afc @ 0x020b3afc, 0x18 bytes, Thumb
 * func_020b3ae4 @ 0x020b3ae4, 0x18 bytes, Thumb
 * func_020b3ac4 @ 0x020b3ac4, 0x20 bytes, Thumb
 * func_020b39bc @ 0x020b39bc, 0x108 bytes, Thumb
 */

struct UnkStruct_020b3ac4 {
    void *unk_00;
};

extern void func_02031ec0(void *p);
extern char data_020e50e8;
extern void func_02031e84(void *a);
extern void func_020edb3c(void *obj);
extern unsigned char data_020e54a8;
extern unsigned char data_021f4b3c;
extern unsigned char data_021f3b56;
extern void *data_021c80bc;
extern int func_ov003_02227394(void *s, int *p1, int *p2, int *p3, int x, int y);
extern unsigned short *func_0204f5e0(void *g, int a, int b, int c, int d, int e);
extern int func_0204bb54(unsigned short *e);
extern int func_0204bb2c(unsigned short *e);
extern int func_020b0594(void *s, int v, int *o1, int *o2, int a, int b, int c, int d);
extern int func_020b65c4(void);

void *func_020b3afc(void *p)
{
    func_02031ec0(p);
    *(unsigned int *) p = (unsigned int) &data_020e50e8;
    return p;
}

void *func_020b3ae4(void *obj)
{
    void *p;

    p = (void *) ((int *) &data_020e50e8);
    *(void **) obj = p;
    func_02031e84(obj);
    return obj;
}

void *func_020b3ac4(struct UnkStruct_020b3ac4 *obj)
{
    obj->unk_00 = ((unsigned char *) &data_020e50e8);
    func_02031e84(obj);
    func_020edb3c(obj);
    return obj;
}

int func_020b39bc(int unused, int *p1, int *p2, int *p3, volatile int x, volatile int y)
{
    unsigned int ok;
    void *g;
    unsigned short *e;
    int v;
    int cx;
    int cy;
    int xx;
    int yy;
    int o1;
    int o2;

    ok = (data_020e54a8 == 0) ? 1 : 0;
    if (ok > 0) {
        if (func_ov003_02227394(&data_021f4b3c, p1, p2, p3, x, y) != 0) {
            goto ret1;
        }
        g = data_021c80bc;
        if (g == 0) {
            goto ret0;
        }
        xx = x;
        yy = y;
        cx = xx >> 4;
        cy = yy >> 4;
        e = func_0204f5e0(g, cx, cy, xx - (cx << 4), yy - (cy << 4), 0);
        if (e == 0) {
            goto ret0;
        }
        if (*e == 0x500a) {
            *p1 = 0xb33;
            *p2 = 0x2000;
            *p3 = 0xa;
            return 1;
        }
        if (func_0204bb54(e) == 0) {
            goto ret0;
        }
        v = func_0204bb2c(e);
        func_020b0594(&data_021f3b56, v, &o1, &o2, 0, 0, 0, 0);
        *p1 = 0x1000;
        *p2 = 0x2000;
        *p3 = 0;
        return 1;
    ret0:
        return 0;
    ret1:
        return 1;
    }
    if (func_020b65c4() != 0x1d) {
        goto ret0b;
    }
    if (x != 3) {
        goto ret0b;
    }
    if (y != 4) {
        goto ret0b;
    }
    *p1 = 0xe66;
    *p2 = 0x2000;
    *p3 = 0xa;
    return 1;
ret0b:
    return 0;
}

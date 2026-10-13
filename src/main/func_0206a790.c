/* func_0206a790 @ 0x0206a790, 0xc2 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206837c(void *);
extern void *func_020ab550(void *, int);
extern void func_020ab5e4(void *);
extern int func_020ab794(void *);
extern int func_020ab798(void *);
extern int func_020a84e4(void *, int, int, int, int, int, int, int, int);
extern void func_020a93e8(void *, int);
extern void func_020ab4bc(void *, int);
extern void func_020a9dc8(void *, void *);
extern void func_020a9d24(void *);

struct func_0206a790_Self {
    unsigned char pad_00[0x24];
    unsigned char *unk_24;
    unsigned char pad_28[0x8];
    unsigned int unk_30;
    unsigned char pad_34[0x4];
    unsigned int unk_38;
};

void func_0206a790(struct func_0206a790_Self *self)
{
    void *n;
    void *a;
    void *b;
    void *c;
    void *d;
    int ax;
    int ay;
    int bx;
    int by;
    int cx;
    int cy;
    int dx;
    int dy;

    n = func_0206837c(self->unk_24);
    a = func_020ab550(n, 0);
    b = func_020ab550(n, 1);
    c = func_020ab550(n, 2);
    d = func_020ab550(n, 3);
    func_020ab5e4(n);

    ax = func_020ab794(a);
    ay = func_020ab798(a);
    bx = func_020ab794(b);
    by = func_020ab798(b);
    cx = func_020ab794(c);
    cy = func_020ab798(c);
    dx = func_020ab794(d);
    dy = func_020ab798(d);

    func_020a93e8(self, func_020a84e4(&self->unk_38, ax, ay, bx, by, cx, cy, dx, dy));
    func_020ab4bc(n, 4);
    func_020a9dc8(self->unk_24 + 0xb4, n);
    func_020a9d24(self->unk_24 + 0xb4);

    self->unk_30 = 5;
}

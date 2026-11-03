/* friend_roster_input_3: 6 functions, module ov119
 * mwccarm 1.2/base -O4,s
 * func_ov119_0229b930 @ 0x0229b930, 0x74 bytes, Thumb
 * func_ov119_0229b8e4 @ 0x0229b8e4, 0x4c bytes, Thumb
 * func_ov119_0229b884 @ 0x0229b884, 0x60 bytes, Thumb
 * func_ov119_0229b828 @ 0x0229b828, 0x5c bytes, Thumb
 * func_ov119_0229b808 @ 0x0229b808, 0x20 bytes, Thumb
 * func_ov119_0229b7e8 @ 0x0229b7e8, 0x20 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xAD];
    unsigned char unk_AD;
    unsigned char unk_AE;
    unsigned char pad_AF[0x2D];
    unsigned char unk_DC[1];
    unsigned char pad_DD[0xDA8 - 0xDC - 1];
    unsigned char unk_DA8[1];
} UnkStruct_0229b884;

typedef struct {
    char pad_00[0xae];
    unsigned char flag; // offset 0xae
    char pad_AF[0xdc - 0xaf];
    char unk_DC[1]; // offset 0xdc
    char pad_DD[0xda8 - 0xdd];
    char obj[1]; // offset 0xda8
} UnkStruct_0229b828;

extern void func_ov002_0220a314(void *);
extern void func_ov002_0220a254(void *);
extern void func_ov002_0220a2b4(void *);
extern int func_ov119_0229ba00(void *);
extern int func_ov119_0229b9c8(void *);
extern void func_ov002_0220a05c(void *, int, int, int, int);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern int func_ov002_02208ae4(void *addr);
extern int func_ov002_02208ad8(void *addr, unsigned char byte);
extern int func_ov002_0220a08c(void *addr, int a, int b, int c);
extern int func_ov002_022090e4(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_0208e4c0(void *, int);
extern int func_ov119_0229a420(void *self, int param);
extern void func_ov002_0220a374(void *ptr, int val);
extern void func_ov002_0220a1dc(void *);
extern void func_ov002_0220a164(void *ptr);

void func_ov119_0229b930(void *self)
{
    int r4;
    int r2;
    unsigned char b;
    unsigned char v = *(unsigned char *) ((char *) self + 0xa0);

    if (v <= 7) {
        func_ov002_0220a314((char *) self + 0xda8);
    } else if (v >= 0xe && v <= 0x15) {
        func_ov002_0220a254((char *) self + 0xda8);
    } else {
        func_ov002_0220a2b4((char *) self + 0xda8);
    }

    r4 = func_ov119_0229ba00(self);
    r2 = func_ov119_0229b9c8(self);
    func_ov002_0220a05c((char *) self + 0xda8, r4, r2, 3, 1);

    b = *(unsigned char *) ((char *) self + 0x8d);
    *(unsigned char *) ((char *) self + 0x9f) = b;

    func_ov002_02208098(self, 3);
}

void func_ov119_0229b8e4(unsigned char *p)
{
    volatile int unused;
    int v1;
    int v2;

    v1 = func_ov002_02208ae4((void *) (p + 0xDC));
    v2 = func_ov002_02208ad8((void *) (p + 0xDC), p[0xAE]);
    func_ov002_0220a08c((void *) (p + 0xDA8), v1, v2, 2);
    p[0x9F] = p[0x8D];
    func_ov002_02208098(p, 3);
}

int func_ov119_0229b884(UnkStruct_0229b884 *p)
{
    int v, w;
    p->unk_AD = 10;
    p->unk_AE = func_ov002_022090e4(&p->unk_DC, 1);
    v = func_ov002_02208ae4(&p->unk_DC);
    w = func_ov002_02208ad8(&p->unk_DC, p->unk_AE);
    func_ov002_0220a0b4(&p->unk_DA8, v, w);
    func_0208e4c0(&p->unk_DA8, 8);
    return (int) func_ov002_02208098(p, 0xB);
}

void func_ov119_0229b828(UnkStruct_0229b828 *self)
{
    int v1;
    int v2;

    if (func_ov119_0229a420(self, 0x10) != 0) {
        self->flag = 2;
    } else {
        self->flag = 0;
    }

    v1 = func_ov002_02208ae4(self->unk_DC);
    v2 = func_ov002_02208ad8(self->unk_DC, self->flag);
    func_ov002_0220a0b4(self->obj, v1, v2);
    func_ov002_0220a374(self->obj, 7);
}

void func_ov119_0229b808(void *arg0)
{
    func_ov002_0220a1dc((char *) arg0 + 0xda8);
    func_ov002_02208098(arg0, 4);
}

void func_ov119_0229b7e8(void *param)
{
    func_ov002_0220a164((char *) param + 0xda8);
    func_ov002_02208098(param, 5);
}

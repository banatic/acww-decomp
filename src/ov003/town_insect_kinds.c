/* town_insect_kinds: 24 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02230554 @ 0x02230554, 0x8 bytes, Thumb
 * func_ov003_022304b0 @ 0x022304b0, 0xa4 bytes, Thumb
 * func_ov003_02230430 @ 0x02230430, 0x80 bytes, Thumb
 * func_ov003_02230428 @ 0x02230428, 0x8 bytes, Thumb
 * func_ov003_02230420 @ 0x02230420, 0x8 bytes, Thumb
 * func_ov003_022303cc @ 0x022303cc, 0x54 bytes, Thumb
 * func_ov003_022303c4 @ 0x022303c4, 0x8 bytes, Thumb
 * func_ov003_02230398 @ 0x02230398, 0x2c bytes, Thumb
 * func_ov003_02230390 @ 0x02230390, 0x8 bytes, Thumb
 * func_ov003_02230364 @ 0x02230364, 0x2c bytes, Thumb
 * func_ov003_0223035c @ 0x0223035c, 0x8 bytes, Thumb
 * func_ov003_02230314 @ 0x02230314, 0x48 bytes, Thumb
 * func_ov003_0223030c @ 0x0223030c, 0x8 bytes, Thumb
 * func_ov003_0223026c @ 0x0223026c, 0xa0 bytes, Thumb
 * func_ov003_02230264 @ 0x02230264, 0x8 bytes, Thumb
 * func_ov003_0223025c @ 0x0223025c, 0x8 bytes, Thumb
 * func_ov003_0223022c @ 0x0223022c, 0x30 bytes, Thumb
 * func_ov003_022301e8 @ 0x022301e8, 0x44 bytes, Thumb
 * func_ov003_022301c4 @ 0x022301c4, 0x22 bytes, Thumb
 * func_ov003_022301bc @ 0x022301bc, 0x8 bytes, Thumb
 * func_ov003_02230198 @ 0x02230198, 0x22 bytes, Thumb
 * func_ov003_02230190 @ 0x02230190, 0x8 bytes, Thumb
 * func_ov003_02230188 @ 0x02230188, 0x8 bytes, Thumb
 * func_ov003_02230180 @ 0x02230180, 0x8 bytes, Thumb
 */

extern void func_ov003_022314fc(void *argument0);
extern void func_ov003_0223055c(void *a, int b, int c, int d, short e);
extern void func_02056fcc(void *a, int b, int c, int d, int e);
extern void func_ov003_02230ce8(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void *func_0209d088(void *a);
extern void NNS_G3dMdlSetMdlAlpha(void *a, int b, int c);
extern void func_ov003_0223345c(void *argument0);
extern void func_ov003_02232d30(void *argument0);
extern void func_ov003_02233674(void *argument0);
extern void func_ov003_02230c3c(void *self, int a, int b, int c, int d, int e);
extern void func_ov003_02230f88(void *self);
extern void func_ov003_022335cc(void *argument0);
extern void func_ov003_02232874(void *argument0);
extern int func_020644cc(int a);
extern void func_ov003_02231f20(void *argument0);
extern void func_ov003_02232640(void *argument0);
extern void func_ov003_022334d8(void *argument0);
extern void func_ov003_022325d4(void *argument0);
extern void func_ov003_02230794(void *argument0);
extern void func_ov003_02231e24(void *argument0);

void func_ov003_02230554(void *argument0)
{
    func_ov003_022314fc(argument0);
}

void func_ov003_022304b0(char *self)
{
    switch (*(signed char *) (self + 0x24d)) {
        case 0x1a:
            func_ov003_0223055c(self, 0xc8, 0x3c, 4, 0x38e);
            break;
        case 0x20:
            func_ov003_0223055c(self, 0x82, 0x3c, 0x10, 0x71c);
            break;
        case 0xe:
            func_ov003_0223055c(self, 0x96, 0x32, 0x18, 0x71c);
            func_02056fcc(self + 0xec, 0, 3, 0x1000, 1);
            break;
        case 0xf:
            func_ov003_0223055c(self, 0x96, 0x32, 0x18, 0x71c);
            func_02056fcc(self + 0xec, 0, 3, 0x1000, 1);
            break;
    }
}

void func_ov003_02230430(char *self)
{
    int t;
    if (*(signed char *) (self + 0x24d) == 0x1e) {
        func_ov003_02230ce8(self, 0, 0x28, 0x50, 0, 0, 0, 0, 4, 0);
    } else {
        func_ov003_02230ce8(self, 0, 0xdc, 0x3c, 0, 0, 0, 0, 1, 0);
    }
    *(short *) (self + 0x232) = 0x168;
    t = *(unsigned char *) (self + 0x251);
    if (t != 0xb && t != 0x10) {
        NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x130), 0, 0);
    }
}

void func_ov003_02230428(void *argument0)
{
    func_ov003_0223345c(argument0);
}

void func_ov003_02230420(void *argument0)
{
    func_ov003_02232d30(argument0);
}

void func_ov003_022303cc(char *self)
{
    if (*(unsigned char *) (self + 0x251) == 0x13) {
        NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x130), 0, 0);
    }
    func_ov003_02230ce8(self, 0, 0x5a, 0x3c, 0, 0, 2, 0, 0, 0);
    *(int *) (self + 0x21c) = 0;
}

void func_ov003_022303c4(void *argument0)
{
    func_ov003_02233674(argument0);
}

void func_ov003_02230398(void *self)
{
    func_ov003_02230c3c(self, 0xc8, 0x3c, 0x25, 0x9, 0x1000);
    func_ov003_02230f88(self);
}

void func_ov003_02230390(void *argument0)
{
    func_ov003_022335cc(argument0);
}

void func_ov003_02230364(void *self)
{
    func_ov003_02230c3c(self, 0x96, 0x1e, 0x25, 0x12, 0x1000);
    func_ov003_02230f88(self);
}

void func_ov003_0223035c(void *argument0)
{
    func_ov003_022335cc(argument0);
}

void func_ov003_02230314(char *self)
{
    func_ov003_02230ce8(self, 0, 0x5a, 0x3c, 0, 0, 0x3c, 0, 8, 1);
    *(int *) (self + 0x21c) = *(unsigned char *) (self + 0x257);
    *(int *) (self + 0x228) = *(int *) (self + 0x208);
}

void func_ov003_0223030c(void *argument0)
{
    func_ov003_02232874(argument0);
}

void func_ov003_0223026c(char *self)
{
    short ang = (short) (func_020644cc(0xb) + 5);
    int *v = (int *) (self + 0x204);
    int t;
    // Assigned in its own statement before the call.
    ang = (short) (0x14 * ang);
    func_ov003_02230ce8(self, ang, 0x5a, 0x40, 0, 0, 0x28, 0, 3, 0);
    t = *(unsigned char *) (self + 0x251);
    if (t != 0xb && t != 0x10) {
        *(int *) (self + 0x21c) = v[0];
        NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x130), 0, 0);
        v[2] -= 0x7d0;
    } else {
        *(short *) (self + 0x238) = -0x4000;
        *(short *) (self + 0x23c) = *(short *) (self + 0x23a);
    }
}

void func_ov003_02230264(void *argument0)
{
    func_ov003_02231f20(argument0);
}

void func_ov003_0223025c(void *argument0)
{
    func_ov003_02232640(argument0);
}

void func_ov003_0223022c(char *self)
{
    func_ov003_02230ce8(self, 0, 0x64, 0x5a, 0, 0, 0, 0, 4, 0);
    *(char *) (self + 0x24c) = 0;
}

void func_ov003_022301e8(char *self)
{
    func_ov003_02230ce8(self, 0, 0x64, 0x50, 0, 0, 0, 0, 5, 0);
    *(char *) (self + 0x24c) = 0;
    func_02056fcc(self + 0xec, 3, 0, 0x1000, 0);
}

void func_ov003_022301c4(void *self)
{
    func_ov003_02230ce8(self, 0, 0x50, 0x50, 0, 0, 0, 0, 1, 0);
}

void func_ov003_022301bc(void *argument0)
{
    func_ov003_022334d8(argument0);
}

void func_ov003_02230198(void *self)
{
    func_ov003_02230ce8(self, 0, 0x50, 0x50, 0, 0, 0, 0, 3, 0);
}

void func_ov003_02230190(void *argument0)
{
    func_ov003_022325d4(argument0);
}

void func_ov003_02230188(void *argument0)
{
    func_ov003_02230794(argument0);
}

void func_ov003_02230180(void *argument0)
{
    func_ov003_02231e24(argument0);
}

/* func_ov003_0223026c @ 0x0223026c, 0xa0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02230ce8(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_020644cc(int a);
extern void *func_0209d088(void *a);
extern void NNS_G3dMdlSetMdlAlpha(void *a, int b, int c);

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

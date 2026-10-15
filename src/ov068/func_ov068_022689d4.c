/* func_ov068_022689d4 @ 0x022689d4, 0xb0 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164a0(void *p, int x);
extern int func_02019de8(void *p);
extern int func_ov068_0226ccb0(void *self, void *other);
extern void func_ov068_0226cce8(void *self, void *other, int x);
extern int func_020121f8(void *p);
extern void func_02016638(void *a, void *b, void *c, int d, int e);
extern char *func_020121e0(void *p, int x);

void func_ov068_022689d4(void *self, char *other)
{
    int val;

    if (func_020164a0(other + 0x334, 0) != 0xd6) {
        return;
    }

    if (func_02019de8(other + 0x564) != 0) {
        *(unsigned char *) ((char *) self + 0x1c) = 2;
        if (func_ov068_0226ccb0(self, other) == 0) {
            func_ov068_0226cce8(self, other, 0);
        }
        return;
    }

    if (((*(unsigned int *) (other + 0x190) << 4) >> 16) >= 8) {
        return;
    }

    val = func_020121f8(other + 0x9b4);

    if (((*(unsigned int *) (other + 0x190) << 4) >> 16) == 7) {
        func_02016638(other + 0x334, other, other + 0x9b4, 0, 7);
    }

    if (val != 0x1000) {
        val += 0x249;
        if (val > 0x1000) {
            val = 0x1000;
        }
    }
    func_020121e0(other + 0x9b4, val);
}

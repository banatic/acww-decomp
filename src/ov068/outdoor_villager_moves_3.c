/* outdoor_villager_moves_3: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_022689d4 @ 0x022689d4, 0xb0 bytes, Thumb
 * func_ov068_0226893c @ 0x0226893c, 0x98 bytes, Thumb
 */

extern int func_020164a0(void *p, int x);
extern int func_02019de8(void *p);
extern int func_ov068_0226ccb0(void *self, void *other);
extern void func_ov068_0226cce8(void *self, void *other, int x);
extern int func_020121f8(void *p);
extern void func_02016638(void *a, void *b, void *c, int d, int e);
extern char *func_020121e0(void *p, int x);
extern int func_0200442c(void *, int, int, int);

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

void func_ov068_0226893c(unsigned char *out, unsigned char *in)
{
    if (func_020164a0(in + 0x334, 0) == 0xcd) {
        if (func_02019de8(in + 0x564) != 0) {
            func_02016638(in + 0x334, in, in + 0x9b4, 0, 7);
            *(unsigned char *) (out + 0x1c) = 2;
            if (func_ov068_0226ccb0(out, in) == 0) {
                func_ov068_0226cce8(out, in, 0);
            }
        } else {
            if (((*(unsigned int *) (in + 0x190) << 4) >> 16) == 7) {
                *(unsigned char *) (in + 0x9f0) = 1;
                func_0200442c(in + 0x514, 0x857, 0x7f, 0);
            }
        }
    }
}

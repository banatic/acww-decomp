/* func_ov068_0226893c @ 0x0226893c, 0x98 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164a0(void *, int);
extern int func_02019de8(void *);
extern void func_02016638(void *, void *, void *, int, int);
extern int func_ov068_0226ccb0(void *, void *);
extern void func_ov068_0226cce8(void *, void *, int);
extern int func_0200442c(void *, int, int, int);

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

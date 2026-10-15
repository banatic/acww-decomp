/* func_ov068_0226918c @ 0x0226918c, 0x44 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern int func_02019c6c(void *, int, unsigned short);
extern unsigned short data_020c80f8;

void func_ov068_0226918c(unsigned char *out, unsigned char *in)
{
    if (func_02019e00(in + 0x564) == 3) {
        if (func_02019de8(in + 0x564) != 0) {
            func_02019c6c(in + 0x564, 2, data_020c80f8);
            out[0x1c] = 1;
        }
    }
}

/* func_ov068_02267b8c @ 0x02267b8c, 0xa8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164a0(void *p, int n);
extern void func_0203e0a8(void *p, int n);
extern int func_02019de8(void *p);
extern int func_0201c2c8(void *p, int n);
extern void func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_0203eddc(void *p);
extern void func_ov068_0226cce8(void *self, void *other, int n);
extern unsigned short data_020c80f8;

void func_ov068_02267b8c(void *self, void *other)
{
    if (func_020164a0((unsigned char *) other + 0x334, 0) == 0xeb ||
        func_020164a0((unsigned char *) other + 0x334, 0) == 0xec) {
        if (((unsigned char *) self)[0x38] >= 3) {
            func_0203e0a8(other, 0);
        }
        if (func_02019de8((unsigned char *) other + 0x564) != 0) {
            if (((unsigned char *) self)[0x38] >= 3) {
                int result = func_0201c2c8(other, 4);
                func_02019d0c((unsigned char *) other + 0x564, 3, 1, 0, 0, 0, result, 0, 0, data_020c80f8, 0);
                ((unsigned char *) self)[0x1c] = 1;
            } else {
                func_0203eddc(other);
                func_ov068_0226cce8(self, other, 0);
                *(unsigned short *) ((unsigned char *) self + 0x3a) = 0x4b0;
            }
        }
    }
}

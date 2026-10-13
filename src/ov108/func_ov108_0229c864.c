/* func_ov108_0229c864 @ 0x0229c864, 0x40 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066830(void *dst, void *src);
extern void func_ov108_0229c8c8(void *self, void *arg);
extern void func_ov108_0229cc90(void *self, void *arg, void *src);

void func_ov108_0229c864(void *self, void *arg)
{
    if (*(unsigned char *) ((char *) self + 0x2ac) == 1) {
        func_02066830((char *) self + 0x1ac, (char *) self + 0xac);
        func_ov108_0229c8c8(self, arg);
        func_ov108_0229cc90(self, arg, (char *) self + 0x1ac);
    }
}

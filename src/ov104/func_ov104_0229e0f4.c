/* func_ov104_0229e0f4 @ 0x0229e0f4, 0x34 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov104_0229ca44(void *);
extern void func_ov104_0229c9fc(void *);

void func_ov104_0229e0f4(void *self)
{
    if (func_0208e484((char *) self + 0x24a0)) {
        if (*(unsigned char *) ((char *) self + 0xb8) == 0x1f) {
            func_ov104_0229ca44(self);
        } else {
            func_ov104_0229c9fc(self);
        }
    }
}

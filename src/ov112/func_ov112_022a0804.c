/* func_ov112_022a0804 @ 0x022a0804, 0x34 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov112_0229ffa0(void *);
extern void func_ov112_0229ffdc(void *);

void func_ov112_022a0804(void *self)
{
    if (func_0208e484((char *) self + 0x4448)) {
        if (*(unsigned char *) ((char *) self + 0xc2)) {
            func_ov112_0229ffa0(self);
        } else {
            func_ov112_0229ffdc(self);
        }
    }
}

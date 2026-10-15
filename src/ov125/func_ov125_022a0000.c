/* func_ov125_022a0000 @ 0x022a0000, 0x30 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void *func_ov002_0220a720(void *ptr, int arg);
extern unsigned char *func_ov002_02208098(void *ptr, unsigned char value);

void func_ov125_022a0000(void *self)
{
    if (func_0208e484((char *) self + 0x644)) {
        func_ov002_0220a720((char *) self + 0x6a8, 9);
        func_ov002_02208098(self, 10);
    }
}

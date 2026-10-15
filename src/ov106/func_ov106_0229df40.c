/* func_ov106_0229df40 @ 0x0229df40, 0x30 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f9c(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov106_0229d57c(void *p, unsigned char value);

void func_ov106_0229df40(unsigned char *self)
{
    if (func_ov002_02209f9c(self + 0x22a0) != 0) {
        func_ov106_0229d57c(self, self[0xb8]);
        func_ov002_02208098((void *) (self), 0x11);
    }
}

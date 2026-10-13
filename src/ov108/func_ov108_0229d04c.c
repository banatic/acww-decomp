/* func_ov108_0229d04c @ 0x0229d04c, 0x38 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b8ac(void *p, int a);
extern void func_ov002_02208098(void *p, unsigned char b);
extern void func_0208e5cc(void *p);

void func_ov108_0229d04c(void *self)
{
    if (func_ov002_0220b8ac((char *) self + 0x28f0, 0)) {
        func_ov002_02208098(self, *((unsigned char *) self + 0x2b3));
        func_0208e5cc((char *) self + 0x2498);
    }
}

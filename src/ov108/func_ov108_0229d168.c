/* func_ov108_0229d168 @ 0x0229d168, 0x44 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern int func_ov002_02209f9c(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov108_0229c2bc(unsigned char *, int);
extern void func_ov108_0229c940(unsigned char *);

void func_ov108_0229d168(unsigned char *self)
{
    if (func_0208e484(self + 0x2498)) {
        func_ov002_02208098((void *) (self), self[0x2b3]);
    }
    if (func_ov002_02209f9c(self + 0x2498)) {
        func_ov108_0229c2bc(self, 0x40);
        func_ov108_0229c940(self);
    }
}

/* func_ov131_0229b1c8 @ 0x0229b1c8, 0x28 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov131_0229af24(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov131_0229b1c8(unsigned char *self)
{
    if (func_0208e484(self + 0x94)) {
        func_ov131_0229af24(self);
        func_ov002_02208098((void *) (self), self[0x1556]);
    }
}

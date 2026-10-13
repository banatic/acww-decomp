/* func_ov099_0229d388 @ 0x0229d388, 0x30 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f9c(void *addr);
extern void func_ov099_0229cfb4(void *self, unsigned char b);
extern void func_ov002_02208098(void *self, int value);

void func_ov099_0229d388(unsigned char *this)
{
    if (func_ov002_02209f9c(this + 0x2274)) {
        func_ov099_0229cfb4(this, this[0x2907]);
        func_ov002_02208098(this, 12);
    }
}

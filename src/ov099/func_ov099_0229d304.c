/* func_ov099_0229d304 @ 0x0229d304, 0x54 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f9c(unsigned char *p);
extern void func_ov099_0229ce68(unsigned char *p);
extern void func_ov099_0229c9d0(unsigned char *p);
extern void func_ov002_02208098(unsigned char *p, int n);
extern void func_ov099_0229cf48(unsigned char *p, unsigned char c, int n);
extern void func_ov099_0229c928(unsigned char *p);

void func_ov099_0229d304(unsigned char *ptr)
{
    if (func_ov002_02209f9c(ptr + 0x2274) == 0) {
        unsigned char c = ptr[0x2909];
        if (ptr[0x2907] == c) {
            func_ov099_0229ce68(ptr);
            func_ov099_0229c9d0(ptr);
            func_ov002_02208098(ptr, 4);
        } else {
            func_ov099_0229cf48(ptr, c, 4);
        }
    } else {
        func_ov099_0229c928(ptr);
    }
}

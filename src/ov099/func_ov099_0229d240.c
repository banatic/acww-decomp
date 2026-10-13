/* func_ov099_0229d240 @ 0x0229d240, 0x38 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d8c(void *ptr);
extern void func_ov099_0229c84c(void *p, unsigned char b);
extern void func_ov099_0229d0f0(void *p);
extern void func_ov099_0229c8f8(void *p);

void func_ov099_0229d240(void *p)
{
    if (func_ov002_02209d8c((char *) p + 0x225c)) {
        func_ov099_0229c84c(p, *((unsigned char *) ((char *) p + 0x2906)));
        func_ov099_0229d0f0(p);
    } else {
        func_ov099_0229c8f8(p);
    }
}

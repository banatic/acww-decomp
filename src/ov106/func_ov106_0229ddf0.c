/* func_ov106_0229ddf0 @ 0x0229ddf0, 0x38 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d8c(void *ptr);
extern void func_ov106_0229cd60(void *ptr, unsigned char b);
extern void func_ov106_0229d73c(void *ptr);
extern void func_ov094_022999d8(void);
extern void func_ov106_0229cde4(void *ptr);

void func_ov106_0229ddf0(void *r4)
{
    if (func_ov002_02209d8c((char *) r4 + 0x2288)) {
        func_ov106_0229cd60(r4, *(unsigned char *) ((char *) r4 + 0xB7));
        ((void) (func_ov106_0229d73c(r4)), func_ov094_022999d8());
    } else {
        func_ov106_0229cde4(r4);
    }
}

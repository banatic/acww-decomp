/* func_ov110_0229d9c8 @ 0x0229d9c8, 0x38 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d8c(void *ptr);
extern void func_ov110_0229cce8(void *ptr, unsigned char b);
extern int func_ov110_0229d840(void *ptr);
extern void func_ov094_022999d8(int a);
extern void func_ov110_0229cd8c(void *ptr);

void func_ov110_0229d9c8(void *p)
{
    if (func_ov002_02209d8c((unsigned char *) p + 0x22c8)) {
        func_ov110_0229cce8(p, ((unsigned char *) p)[0xf4]);
        func_ov094_022999d8(func_ov110_0229d840(p));
    } else {
        func_ov110_0229cd8c(p);
    }
}

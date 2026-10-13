/* func_ov103_0229c8a4 @ 0x0229c8a4, 0x44 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066830(void *, void *);
extern void func_ov103_0229c910(void *, void *);
extern void func_ov103_0229cd1c(void *, void *, void *);

void func_ov103_0229c8a4(unsigned char *p, void *q)
{
    if (p[0x2da0] == 1) {
        func_02066830(p + 0x2ca0, p + 0x2ba0);
        func_ov103_0229c910(p, q);
        func_ov103_0229cd1c(p, q, p + 0x2ca0);
    }
}

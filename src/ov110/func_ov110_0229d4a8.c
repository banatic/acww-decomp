/* func_ov110_0229d4a8 @ 0x0229d4a8, 0x5c bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d5e4(void *, int);
extern int func_ov110_0229d5d4(void *, int);
extern int func_ov110_0229d0b8(void *, int);
extern int func_ov110_0229d078(void *, int);
extern void func_ov110_0229d458(void *, int, int, int);
extern void func_ov110_0229cce8(void *, int);

int func_ov110_0229d4a8(void *p0, int p1)
{
    int v;

    if (func_ov110_0229d5e4(p0, p1) == 0 && func_ov110_0229d5d4(p0, p1) == 0) {
        goto ret0;
    }

    v = func_ov110_0229d0b8(p0, p1);
    if (v != 0xfff1) {
        func_ov110_0229d458(p0, *(unsigned char *) ((char *) p0 + 0xf4), v, func_ov110_0229d078(p0, p1));
    }
    func_ov110_0229cce8(p0, p1);
    return 1;

ret0:
    return 0;
}

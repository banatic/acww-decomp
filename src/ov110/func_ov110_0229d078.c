/* func_ov110_0229d078 @ 0x0229d078, 0x40 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d5e4(const char *, int);
extern int func_ov110_0229d5d4(const char *, int);
extern int func_ov110_0229d590(const char *, int);
extern int func_ov094_0229aa84(void *, int);

int func_ov110_0229d078(const char *p, int q)
{
    int v;

    if (func_ov110_0229d5e4(p, q) == 0 && func_ov110_0229d5d4(p, q) == 0) {
        goto return_0xf1;
    }
    v = func_ov110_0229d590(p, q);
    return func_ov094_0229aa84((char *) p + 0x138, v);

return_0xf1:
    return 0xF1;
}

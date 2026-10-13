/* func_ov110_0229d17c @ 0x0229d17c, 0x3c bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d1b8(char *p, int i);
extern int func_ov110_0229d590(char *p, int i);
extern void func_ov094_0229a888(char *p, int v);

void func_ov110_0229d17c(char *p)
{
    unsigned char i = 0;
    char *q = p + 0x138;
    do {
        if (func_ov110_0229d1b8(p, i)) {
            func_ov094_0229a888(q, func_ov110_0229d590(p, i));
        }
        i++;
    } while (i <= 14);
}

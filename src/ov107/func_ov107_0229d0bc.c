/* func_ov107_0229d0bc @ 0x0229d0bc, 0x34 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov107_0229d388(char *p, int q);
extern int func_ov107_0229d36c(char *p, int q);
extern int func_ov094_0229aa84(char *p, int v);

int func_ov107_0229d0bc(char *p, int q)
{
    if (func_ov107_0229d388(p, q) != 0) {
        return func_ov094_0229aa84(p + 0x10c, func_ov107_0229d36c(p, q));
    } else {
        return 0xf1;
    }
}

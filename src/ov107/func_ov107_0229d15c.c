/* func_ov107_0229d15c @ 0x0229d15c, 0x34 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov107_0229d388(char *p1, int p2);
extern int func_ov107_0229d36c(char *p1, int p2);
extern int func_ov094_0229a8bc(char *p1, int p2);

int func_ov107_0229d15c(char *p1, int p2)
{
    if (func_ov107_0229d388(p1, p2) != 0) {
        return func_ov094_0229a8bc(p1 + 0x10c, func_ov107_0229d36c(p1, p2));
    } else {
        return 0;
    }
}

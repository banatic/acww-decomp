/* func_ov108_0229cc20 @ 0x0229cc20, 0x3c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov108_0229cd70(unsigned char *p, int a);
extern int func_ov108_0229cd5c(unsigned char *p, int a);
extern int func_ov094_0229b384(unsigned char *p, int a);

int func_ov108_0229cc20(unsigned char *a0, int a1)
{
    if (func_ov108_0229cd70(a0, a1) != 0) {
        return func_ov094_0229b384(a0 + 0xd50, func_ov108_0229cd5c(a0, a1));
    } else {
        if (a1 == 0x15) {
            return 0xbc;
        } else {
            return 0;
        }
    }
}

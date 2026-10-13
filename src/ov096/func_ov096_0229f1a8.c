/* func_ov096_0229f1a8 @ 0x0229f1a8, 0x58 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f830(unsigned char *a, int b);
extern int func_ov096_0229f7ac(unsigned char *a, int b);
extern int func_ov096_0229f820(unsigned char *a, int b);
extern int func_ov096_0229f548(unsigned char *a, int b);
extern int func_ov094_0229a8bc(unsigned char *a, int b);
extern int func_ov094_0229b788(unsigned char *a, int b);

int func_ov096_0229f1a8(unsigned char *arg0, int arg1)
{
    if (func_ov096_0229f830(arg0, arg1) != 0) {
        return func_ov094_0229a8bc(arg0 + 0x358, func_ov096_0229f7ac(arg0, arg1));
    } else if (func_ov096_0229f820(arg0, arg1) != 0) {
        return func_ov094_0229b788(arg0 + 0xdb8, func_ov096_0229f548(arg0, arg1));
    }
    return 0;
}

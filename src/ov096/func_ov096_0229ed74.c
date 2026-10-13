/* func_ov096_0229ed74 @ 0x0229ed74, 0x78 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f830(char *obj, int arg);
extern int func_ov096_0229f7ac(char *obj, int arg);
extern int func_ov096_0229f820(char *obj, int arg);
extern int func_ov096_0229f548(char *obj, int arg);
extern void func_ov094_0229b98c(char *p);
extern void func_ov094_0229ab1c(char *p, int arg);
extern void func_ov094_0229ab5c(char *p);
extern void func_ov094_0229b950(char *p, int arg);

void func_ov096_0229ed74(char *obj, int arg)
{
    if (func_ov096_0229f830(obj, arg)) {
        int res = func_ov096_0229f7ac(obj, arg);
        func_ov094_0229b98c(obj + 0xdb8);
        func_ov094_0229ab1c(obj + 0x358, res);
    } else {
        if (func_ov096_0229f820(obj, arg)) {
            int res = func_ov096_0229f548(obj, arg);
            func_ov094_0229ab5c(obj + 0x358);
            func_ov094_0229b950(obj + 0xdb8, res);
        } else {
            func_ov094_0229ab5c(obj + 0x358);
            func_ov094_0229b98c(obj + 0xdb8);
        }
    }
}

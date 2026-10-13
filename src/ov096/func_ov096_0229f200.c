/* func_ov096_0229f200 @ 0x0229f200, 0x90 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f830(int, int);
extern int func_ov096_0229f7ac(int, int);
extern int func_ov096_0229f820(int, int);
extern int func_ov096_0229f548(int, int);
extern int func_ov096_0229f810(int, int);
extern int func_ov096_0229f800(int, int);
extern int func_ov094_0229ab90(int, int);
extern int func_ov094_0229b328(int, int);

int func_ov096_0229f200(int param1, int param2)
{
    if (func_ov096_0229f830(param1, param2)) {
        return func_ov094_0229ab90(param1 + 0x358, func_ov096_0229f7ac(param1, param2));
    }
    if (func_ov096_0229f820(param1, param2)) {
        return func_ov094_0229b328(param1 + 0xdb8, func_ov096_0229f548(param1, param2));
    }
    if (func_ov096_0229f810(param1, param2)) {
        return 8;
    }
    if (func_ov096_0229f800(param1, param2)) {
        return func_ov094_0229ab90(param1 + 0x358, func_ov096_0229f7ac(param1, param2));
    }
    if (param2 == 0x21) {
        return 0xb0;
    }
    return 0;
}

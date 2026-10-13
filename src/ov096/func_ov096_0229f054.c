/* func_ov096_0229f054 @ 0x0229f054, 0x34 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f820(int, int);
extern int func_ov096_0229f548(int, int);
extern int func_ov094_0229b8d8(char *, int);

int func_ov096_0229f054(int arg0, int arg1)
{
    if (func_ov096_0229f820(arg0, arg1) == 0) {
        return 0;
    }
    return func_ov094_0229b8d8((char *) arg0 + 0xDB8, func_ov096_0229f548(arg0, arg1));
}

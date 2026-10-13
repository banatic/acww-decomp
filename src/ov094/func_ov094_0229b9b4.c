/* func_ov094_0229b9b4 @ 0x0229b9b4, 0x20 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229b8d8(int, int);
extern int func_ov094_0229b9d4(int, int, int);

int func_ov094_0229b9b4(int a, int b, int c)
{
    return func_ov094_0229b9d4(a, b, func_ov094_0229b8d8(a, c));
}

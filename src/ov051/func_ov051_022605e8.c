/* func_ov051_022605e8 @ 0x022605e8, 0x20 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_020950c0(int);

unsigned char func_ov051_022605e8(int a, int b)
{
    int t;
    t = func_020984e8();
    t = func_02099870(t);
    t = func_020950c0(t);
    return (unsigned char) (b + (unsigned char) t);
}

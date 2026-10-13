/* func_020535f0 @ 0x020535f0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bc64(unsigned short *p);
extern int func_02053624(int x);

int func_020535f0(unsigned short *p)
{
    unsigned int v;
    int flag;

    flag = 0;
    v = *p;
    if (v >= 0x450c && v <= 0x45db) {
        flag = 1;
    }
    if (flag != 0) {
        return func_02053624(func_0204bc64(p));
    }
    return 0;
}

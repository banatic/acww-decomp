/* func_0209bc54 @ 0x0209bc54, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209bc94(int);
extern int func_0209bcb8(int);
extern int data_020d1a6c[];

int func_0209bc54(int *out, int val)
{
    int i = func_0209bc94(val);
    int ret = 0;
    if (func_0209bcb8(i) != 0) {
        *out = val - data_020d1a6c[i];
        ret = 1;
    }
    return ret;
}

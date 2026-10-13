/* func_0209bcd4 @ 0x0209bcd4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209bd10(int);
extern int func_0209bd24(int);
extern int data_020d1a40[];

int func_0209bcd4(int *out, int val)
{
    int idx = func_0209bd10(val);
    if (func_0209bd24(idx) != 0) {
        *out = val - data_020d1a40[idx];
        return 1;
    }
    return 0;
}

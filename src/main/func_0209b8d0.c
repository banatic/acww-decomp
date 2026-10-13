/* func_0209b8d0 @ 0x0209b8d0, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209bd10(int);
extern int func_0209bcd4(int *, int);
extern int data_020d1a7c[];

int func_0209b8d0(int param)
{
    if (func_0209bd10(param) == 0) {
        int idx = 0;
        if (func_0209bcd4(&idx, param) != 0) {
            return data_020d1a7c[idx];
        }
    }
    return 0;
}

/* func_0201240c @ 0x0201240c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020124e4(int arg0, int arg1, int arg2, int arg3);

void func_0201240c(int arg0, unsigned short *arg1, int arg2, int arg3)
{
    int cond = 0;
    unsigned short val = *arg1;

    if (val >= 0x1376 && val <= 0x1376) {
        cond = 1;
    }

    if (cond != 0 || (val >= 0x1377 && val <= 0x1377)) {
        func_020124e4(arg0, 1, arg2, arg3);
    }
}

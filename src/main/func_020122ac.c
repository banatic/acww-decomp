/* func_020122ac @ 0x020122ac, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020124e4(int a, int b, int c, int d);

void func_020122ac(int arg0, unsigned short *arg1, int arg2, int arg3)
{
    int cond = 0;
    unsigned short val = *arg1;

    if (val >= 0x1376 && val <= 0x1376) {
        cond = 1;
    }

    if (cond != 0 || (val >= 0x1377 && val <= 0x1377)) {
        func_020124e4(arg0, 18, arg2, arg3);
    }
}

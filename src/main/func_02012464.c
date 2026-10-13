/* func_02012464 @ 0x02012464, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020124e4(int arg0, int arg1, int arg2, int arg3);

void func_02012464(int arg0, unsigned short *arg1, int arg2, int arg3)
{
    int cond = 0;
    unsigned short val = *arg1;

    if (val >= 0x1376 && val <= 0x1376) {
        cond = 1;
    }

    if (cond != 0 || (val >= 0x1377 && val <= 0x1377)) {
        func_020124e4(arg0, 0, arg2, arg3);
        return;
    }

    cond = 0;
    if (val >= 0x1374 && val <= 0x1374) {
        cond = 1;
    }

    if (cond != 0 || (val >= 0x1375 && val <= 0x1375)) {
        func_020124e4(arg0, 0x13, 0, 0);
        return;
    }

    if (val >= 0x1380 && val <= 0x139f) {
        func_020124e4(arg0, 0x25, 0, 0);
    }
}

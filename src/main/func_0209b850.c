/* func_0209b850 @ 0x0209b850, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1a60[];

int func_0209b850(int r0)
{
    int r3;
    int r1;

    r3 = 0;
    while (r3 < 10) {
        r1 = data_020d1a60[r3];
        if (r0 == r1) {
            return r3;
        }
        r3++;
    }
    return -1;
}

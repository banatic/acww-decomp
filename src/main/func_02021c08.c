/* func_02021c08 @ 0x02021c08, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021dc7bc[];

func_02021c08(int r0, int r1)
{
    int r5 = func_02081d60(r1);
    int r6 = 0;
    int r4 = 0;
    if (func_02081398(r0, r5) == 1) {
        r4 = 1;
    }
    if (r4 != 0) {
        if (func_0209871c((unsigned int) data_021dc7bc, r5) != -1) {
            r6 = 1;
        }
    }
    return r6;
}

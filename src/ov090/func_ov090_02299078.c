/* func_ov090_02299078 @ 0x02299078, 0x20 bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov090_02299960;

unsigned char func_ov090_02299078(unsigned char x)
{
    data_ov090_02299960 = 0xa;
    if (x > 6) {
        return x;
    }
    if (x == 6) {
        return 0;
    }
    return x + 1;
}

/* func_ov090_02299098 @ 0x02299098, 0x20 bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov090_02299960;
unsigned char func_ov090_02299098(unsigned char x)
{
    if (x > 6) {
        return x;
    }
    data_ov090_02299960 = 10;
    if (x == 0) {
        return 6;
    }
    return (unsigned char) (x - 1);
}

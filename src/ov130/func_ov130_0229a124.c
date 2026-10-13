/* func_ov130_0229a124 @ 0x0229a124, 0x12 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

int func_ov130_0229a124(unsigned char *p)
{
    int result = 1;
    if (p[5] != 0xb && p[5] != 0xc) {
        result = 0;
    }
    return result;
}

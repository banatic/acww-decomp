/* func_ov140_0229a1a4 @ 0x0229a1a4, 0x1e bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

int func_ov140_0229a1a4(int unused, const unsigned char *data)
{
    if (data[32] == 6 && (data[0] || data[1])) {
        return 1;
    }
    return 0;
}

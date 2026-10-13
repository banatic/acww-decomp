/* func_02077a14 @ 0x02077a14, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02077a14(unsigned char *out, int val, int ctrl)
{
    out[0] = ((ctrl << 4) & 0xF0) | ((val >> 16) & 0x0F);
    out[1] = (unsigned char) (val >> 8);
    out[2] = (unsigned char) val;
}

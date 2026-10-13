/* func_020ff994 @ 0x020ff994, 0x68 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fd278;
extern void VEC_Normalize(int *a, int *b);

void func_020ff994(int *out)
{
    data_021fd278 = data_021fd278 * 0x5eedf715 + 0x1b0cb173;
    out[0] = data_021fd278 >> 8;
    data_021fd278 = data_021fd278 * 0x5eedf715 + 0x1b0cb173;
    out[1] = data_021fd278 >> 8;
    data_021fd278 = data_021fd278 * 0x5eedf715 + 0x1b0cb173;
    out[2] = data_021fd278 >> 8;
    VEC_Normalize(out, out);
}

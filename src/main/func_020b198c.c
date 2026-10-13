/* func_020b198c @ 0x020b198c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020b198c(unsigned short *param0, int param1)
{
    unsigned short *ptr;
    unsigned short val;
    int shift;

    ptr = (unsigned short *) ((unsigned int) param0 + 0x4A0);
    val = *ptr;
    shift = 1 << param1;
    val &= ~shift;
    *ptr = val;
}

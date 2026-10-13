/* func_ov139_022995a0 @ 0x022995a0, 0x10 bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

void func_ov139_022995a0(unsigned short *param0, unsigned short param1)
{
    unsigned short *ptr;
    unsigned short val;

    ptr = (unsigned short *) ((char *) param0 + 0x9a0);
    val = *ptr;
    val &= ~param1;
    *ptr = val;
}

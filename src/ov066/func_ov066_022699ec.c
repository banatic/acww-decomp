/* func_ov066_022699ec @ 0x022699ec, 0x28 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov066_0226bdf8;

unsigned int func_ov066_022699ec(void)
{
    unsigned int next = data_ov066_0226bdf8 * 0x5eedf715u + 0x1b0cb173u;
    data_ov066_0226bdf8 = next;
    return next;
}

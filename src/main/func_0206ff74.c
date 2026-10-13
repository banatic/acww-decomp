/* func_0206ff74 @ 0x0206ff74, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021cfccc[];

void func_0206ff74(int bit)
{
    data_021cfccc[bit >> 5] &= ~(1u << (bit & 31));
}

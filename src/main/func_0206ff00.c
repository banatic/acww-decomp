/* func_0206ff00 @ 0x0206ff00, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021cfcb4[];

void func_0206ff00(int bit)
{
    data_021cfcb4[bit >> 5] &= ~(1u << (bit & 31));
}

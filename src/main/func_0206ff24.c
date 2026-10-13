/* func_0206ff24 @ 0x0206ff24, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021cfcb4[];

void func_0206ff24(int arg)
{
    data_021cfcb4[arg >> 5] |= (1u << (arg & 31));
}

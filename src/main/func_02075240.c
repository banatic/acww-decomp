/* func_02075240 @ 0x02075240, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void (*data_020ccff0[])(unsigned char *payload, unsigned int length, int player);

void func_02075240(unsigned char *payload, unsigned int length, int player, int index)
{
    data_020ccff0[index](payload, length, player);
}

/* func_020b1730 @ 0x020b1730, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021f4b08[2];

void func_020b1730(int bit)
{
    if (bit >= 32) {
        data_021f4b08[1] |= 1u << (bit - 32);
    } else {
        data_021f4b08[0] |= 1u << bit;
    }
}

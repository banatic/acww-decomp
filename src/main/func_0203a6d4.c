/* func_0203a6d4 @ 0x0203a6d4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021f3a86[];

int func_0203a6d4(unsigned int index)
{
    if (index < 15) {
        return data_021f3a86[index];
    } else {
        return 0xfff1;
    }
}

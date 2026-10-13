/* func_0203a744 @ 0x0203a744, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern const unsigned short data_021f3a68[];

int func_0203a744(void)
{
    int i;
    const unsigned short *table = data_021f3a68;

    for (i = 0; i < 15; i++) {
        if (table[i] != 0xfff1) {
            return 1;
        }
    }
    return 0;
}

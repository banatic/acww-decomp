/* func_02034a18 @ 0x02034a18, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021c5204[];
extern unsigned short data_021c519c[];

void func_02034a18(void)
{
    unsigned int i;
    for (i = 0; i < 51; i++) {
        data_021c5204[i] = 0xfff1;
        data_021c519c[i] = data_021c5204[i];
    }
}

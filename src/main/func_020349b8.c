/* func_020349b8 @ 0x020349b8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021c5204[];
extern unsigned short data_021c5174[];

unsigned short *func_020349b8(unsigned int index)
{
    if (index < 0x33) {
        return &data_021c5204[index];
    }
    return data_021c5174;
}

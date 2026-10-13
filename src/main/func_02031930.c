/* func_02031930 @ 0x02031930, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct {
    unsigned short value;
    unsigned char pad[28];
} data_020c907c[];

unsigned short func_02031930(int idx)
{
    if (idx < 0x7c) {
        return data_020c907c[idx].value;
    }
    return 0xffff;
}

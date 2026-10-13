/* func_020b7074 @ 0x020b7074, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020d20d0[];

extern struct {
    unsigned char pad[8];
    unsigned char : 2;
    unsigned char field : 6;
} data_021ebcc8;

unsigned short func_020b7074(void)
{
    if ((int) data_021ebcc8.field < 12) {
        return data_020d20d0[data_021ebcc8.field];
    } else {
        return data_020d20d0[0];
    }
}

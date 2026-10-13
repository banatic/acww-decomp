/* func_02062b18 @ 0x02062b18, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020627bc(unsigned short *ptr);
extern int data_021cb5bc;
extern int data_021cb5c4;

void func_02062b18(void)
{
    unsigned short data[2];
    unsigned int i;

    data_021cb5bc = 0;
    data_021cb5c4 = 0;

    for (i = 0; i < 0x40; i++) {
        data[0] = (i < 0x40) ? (unsigned short) (i + 0x13c8) : 0x13c8;
        if (func_020627bc(data) == 0x1d) {
            data_021cb5c4++;
        }
    }

    for (i = 0; i < 0x20; i++) {
        data[1] = (i < 0x20) ? (unsigned short) (i + 0x13a8) : 0x13a8;
        if (func_020627bc(&data[1]) == 0x1d) {
            data_021cb5bc++;
        }
    }
}

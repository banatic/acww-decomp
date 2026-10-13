/* func_02045670 @ 0x02045670, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b710(unsigned short *ptr);
extern unsigned short data_020ca670[];

unsigned short func_02045670(int unused, int id)
{
    unsigned short key;

    if (id != 0x5b) {
        if (id == 0xcc) {
            return 0x1548;
        }
    } else {
        return 0x14b8;
    }

    key = 0xfff1;
    key = (unsigned short) id;

    return data_020ca670[func_0204b710(&key)];
}

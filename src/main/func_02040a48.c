/* func_02040a48 @ 0x02040a48, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern int data_021dc7a8[];
extern unsigned short data_021c7580;
extern int func_020984d4(void);

int func_02040a48(int param)
{
    unsigned char *base = (unsigned char *) data_021dc7a8;
    int r = 0;

    if (param == base[0x1722a]) {
        int v = func_020984d4();

        if (v == 7) {
            if (data_021c7580 == 0xff) {
                r = 1;
            }
        } else {
            if ((data_021c7580 >> v) & 1) {
                r = 1;
            }
        }
    }

    return r;
}

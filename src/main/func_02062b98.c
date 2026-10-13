/* func_02062b98 @ 0x02062b98, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204be38(const unsigned short *);
extern int func_0204bd84(const unsigned short *);
extern int data_021cb5b4;
extern int data_021cb5b8;

void func_02062b98(void)
{
    unsigned short local[2];
    unsigned i = 0;

    for (; i < 0x21; i++) {
        local[0] = (i < 0x21) ? (unsigned short) (i + 0x1408) : (unsigned short) 0x1408;
        local[1] = (i < 0x21) ? (unsigned short) (i + 0x1471) : (unsigned short) 0x1471;

        if (func_0204be38(local)) {
            data_021cb5b4++;
        } else {
            if (func_0204bd84(&local[1])) {
                data_021cb5b8++;
            }
        }
    }
}

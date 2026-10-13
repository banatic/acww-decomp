/* func_ov105_0229c438 @ 0x0229c438, 0x58 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_02088d34(unsigned short *, int, int, int, int);
extern unsigned short data_ov105_0229fa80[];

struct UnkStruct_0229c438 {
    char pad_00[0x2c0];
    unsigned char unk_2C0;
};

int func_ov105_0229c438(struct UnkStruct_0229c438 *p0, int p1, int p2)
{
    int a = p1 - 0x80;
    int b = p2 - 0x60;
    int i = 0;
    int j = 0;

    while (i < 2) {
        if (i != p0->unk_2C0) {
            if (func_02088d34(&data_ov105_0229fa80[j * 4], a, b, 2, 2) != 0) {
                p0->unk_2C0 = (unsigned char) i;
                return 1;
            }
        }
        i++;
        j += 3;
    }
    return 0;
}

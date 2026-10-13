/* func_ov102_0229c364 @ 0x0229c364, 0x58 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_02088d34(unsigned short *, int, int, int, int);
extern unsigned short data_ov102_0229eac0[];

struct UnkStruct_0229c364 {
    char pad_00[0x25aa];
    unsigned char unk_25AA;
};

int func_ov102_0229c364(struct UnkStruct_0229c364 *p0, int p1, int p2)
{
    int a = p1 - 0x80;
    int b = p2 - 0x60;
    int i = 0;
    int j = 0;

    while (i < 6) {
        if (i != p0->unk_25AA) {
            if (func_02088d34(&data_ov102_0229eac0[j * 4], a, b, 2, 2) != 0) {
                p0->unk_25AA = (unsigned char) i;
                return 1;
            }
        }
        i++;
        j += 3;
    }
    return 0;
}

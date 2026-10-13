/* func_ov127_02299d20 @ 0x02299d20, 0x44 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

struct Entry {
    unsigned int unk_00;
    unsigned int unk_04;
};

extern struct Entry data_ov127_0229b614[];
extern int func_02088d34(struct Entry *, int, int, int, int);

int func_ov127_02299d20(int unused, int a, int b)
{
    int x = a - 0x80;
    int y = b - 0x60;
    unsigned char i = 0;

    while (i < 4) {
        if (func_02088d34(&data_ov127_0229b614[i], x, y, 2, 2)) {
            return i;
        }
        i = (unsigned char) (i + 1);
    }

    return 4;
}

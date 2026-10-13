/* func_ov123_0229ae24 @ 0x0229ae24, 0x50 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

struct UnkStruct_0229ae24 {
    char pad_00[0xA4];
    unsigned char flag;
    char pad_A5[3];
    unsigned char x;
    unsigned char y;
};

void func_ov123_0229ae24(struct UnkStruct_0229ae24 *self)
{
    int a;
    int b;

    a = data_021f6c58;
    b = data_021f6c54 + 16;
    if (self->flag == 1) {
        a += 2;
        b += 2;
    }
    a -= 64;
    if (a < 0) {
        a = 0;
    } else if (a > 127) {
        a = 127;
    }
    b -= 24;
    if (b < 0) {
        b = 0;
    } else if (b > 127) {
        b = 127;
    }
    self->x = a >> 2;
    self->y = b >> 2;
}

/* func_ov095_0229aff0 @ 0x0229aff0, 0x68 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_02088cf4(int, int, int, int, int, int);
extern void RtcSendPxiCommand(int);

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

struct UnkStruct_0229aff0 {
    char pad_00[0x16];
    unsigned char unk_16;
    char pad_17[0x2d];
    int unk_44;
};

int func_ov095_0229aff0(struct UnkStruct_0229aff0 *self)
{
    int result, val;
    result = func_02088cf4(self->unk_44, 3, (int) data_021f6c58 - 0x80, (int) data_021f6c54 - 0x60, 2, 2);
    if (result == -1) {
        return 0;
    }
    val = result;
    switch (result) {
        case 0:
            val = 4;
            break;
        case 1:
            val = 1;
            break;
        case 2:
            val = 2;
            break;
    }
    if (val == self->unk_16) {
        return 0;
    }
    self->unk_16 = (unsigned char) val;
    RtcSendPxiCommand(0x18);
    return 1;
}

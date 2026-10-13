/* func_ov147_0229a594 @ 0x0229a594, 0x72 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a594 {
    int pad_00;
    int pad_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int pad_18;
    unsigned char unk_1C;
};

int func_ov147_0229a594(struct UnkStruct_0229a594 *self)
{
    int cond;
    int result;

    cond = (self->unk_0C == 2) ? 1 : 0;
    if (cond != 0) {
        self->unk_1C = 1;
        self->unk_14 = 0;
    }
    if (self->unk_1C != 0) {
        self->unk_10--;
        if (self->unk_10 <= 0) {
            self->unk_1C = 0;
        }
    } else {
        self->unk_10++;
        if (self->unk_10 >= 10) {
            self->unk_10 = 10;
            self->unk_14++;
            if (self->unk_14 > 5) {
                self->unk_1C = 1;
                self->unk_14 = 0;
            }
        }
    }
    result = 0;
    if (self->unk_10 > 0) {
        // result stays 0
    } else if (cond != 0) {
        result = 1;
    } else if (self->unk_08 != self->unk_0C) {
        result = 1;
    }
    return result;
}

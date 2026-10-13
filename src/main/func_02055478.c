/* func_02055478 @ 0x02055478, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fbe94;
extern int func_020e9948(int, int);

struct inner {
    unsigned char pad_00[0x17];
    unsigned char unk_17;
};

struct outer {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    struct inner *inner_ptr;
    unsigned char pad_10[0x3c - 0x10];
    unsigned int unk_3C;
};

int func_02055478(struct outer *self, int flag)
{
    int offset;
    int result;

    offset = self->inner_ptr->unk_17 * 0x58;

    if (flag == 0) {
        flag = data_021fbe94;
    }

    result = func_020e9948(flag, offset);

    if (result == 0) {
        return 0;
    }

    self->unk_3C = result;
    self->unk_08 |= 1;
    return 1;
}

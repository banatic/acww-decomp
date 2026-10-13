/* func_0205989c @ 0x0205989c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057bf0(int);

struct UnkStruct_0205989c {
    unsigned char pad_00[0xc8];
    unsigned char unk_C8;
};

int func_0205989c(struct UnkStruct_0205989c *self)
{
    int result = 1;
    int flag = 1;
    if (!(self->unk_C8 == 2 || (self->unk_C8 == 1 && func_02057bf0(1) == 0))) {
        flag = 0;
    }
    if (flag == 0) {
        if (!(self->unk_C8 == 7 && func_02057bf0(7) == 0)) {
            result = 0;
        }
    }
    return result;
}

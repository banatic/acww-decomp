/* func_02066f2c @ 0x02066f2c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern short data_020def1c[];
extern void func_02068d74(void *ptr, int val);
extern void func_020689b4(void *ptr);

struct UnkStruct_02066f2c {
    char pad_00[0x8];
    int unk_08;
    int unk_0C;
    char pad_10[0xC];
    char unk_1C;
    char pad_1D[0x7F];
    int unk_9C;
    char pad_A0[0x198C];
    char unk_1A2C;
    char pad_1A2D[0x46B];
    unsigned char unk_1E98;
};

void func_02066f2c(struct UnkStruct_02066f2c *self)
{
    int flag = 0;
    if (self->unk_0C > 0) {
        self->unk_0C--;
    } else {
        flag = 1;
    }
    self->unk_9C = data_020def1c[self->unk_0C];
    func_02068d74(&self->unk_1C, self->unk_9C);
    if (flag) {
        if (self->unk_1E98 == 0) {
            func_020689b4(&self->unk_1A2C);
        }
        self->unk_08 = 3;
    }
}

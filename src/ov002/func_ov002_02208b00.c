/* func_ov002_02208b00 @ 0x02208b00, 0x12 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02208b00 {
    unsigned char pad_00[0x1c];
    unsigned char unk_1C;
};

extern int func_ov002_02208b14(struct UnkStruct_02208b00 *self, int arg1, int arg2, int arg3);

int func_ov002_02208b00(struct UnkStruct_02208b00 *self, int arg1, int arg2)
{
    return func_ov002_02208b14(self, arg1, arg2, self->unk_1C - 1);
}

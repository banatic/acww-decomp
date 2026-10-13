/* func_ov144_02299b48 @ 0x02299b48, 0x32 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02299b48 {
    char pad_00[0xBA];
    short unk_BA;
} UnkStruct_02299b48;

extern void func_ov144_02299670(UnkStruct_02299b48 *self, int value);
extern void func_ov144_02299b7c(UnkStruct_02299b48 *self);

int func_ov144_02299b48(UnkStruct_02299b48 *self, int value)
{
    int changed = (self->unk_BA != value);
    self->unk_BA = value;
    func_ov144_02299670(self, 8);
    func_ov144_02299b7c(self);
    return changed;
}

/* func_ov003_022108b0 @ 0x022108b0, 0x10 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x7e4];
    short unk_7E4;
} UnkStruct_022108b0;

extern int func_0200fb34(UnkStruct_022108b0 *self, short val);

int func_ov003_022108b0(UnkStruct_022108b0 *self)
{
    return func_0200fb34(self, self->unk_7E4);
}

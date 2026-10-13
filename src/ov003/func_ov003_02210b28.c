/* func_ov003_02210b28 @ 0x02210b28, 0x10 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200fb34(void *self, short val);

typedef struct {
    char pad_00[0x7d6];
    short unk_7D6;
} UnkStruct_02210b28;

void func_ov003_02210b28(UnkStruct_02210b28 *self)
{
    func_0200fb34(self, self->unk_7D6);
}

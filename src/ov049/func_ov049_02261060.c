/* func_ov049_02261060 @ 0x02261060, 0x20 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206844c(void *a, void *b, void *c);
extern void *data_ov049_02263298;

struct UnkStruct_02261060 {
    char pad_00[0x40];
    void *unk_40;
};

int func_ov049_02261060(struct UnkStruct_02261060 *self)
{
    char c = 0x12;
    return func_0206844c(self->unk_40, &c, data_ov049_02263298);
}

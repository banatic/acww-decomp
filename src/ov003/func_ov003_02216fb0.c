/* func_ov003_02216fb0 @ 0x02216fb0, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02008258(void *self, int value);
extern int func_02056f94(void *ptr);
extern void func_ov003_02216eb4(void *self, int a, int b);

typedef struct UnkStruct_02216fb0 {
    char pad_00[0x2d0];
    char unk_2D0;
    char pad_2D1[0x7f0 - 0x2d0 - 1];
    unsigned int unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    unsigned int unk_7FC;
} UnkStruct_02216fb0;

void func_ov003_02216fb0(UnkStruct_02216fb0 *self)
{
    self->unk_7FC = func_02008258(self, self->unk_7F0);
    if (func_02056f94(&self->unk_2D0) != 0) {
        func_ov003_02216eb4(self, 6, -1);
    }
}

/* func_ov003_02216b34 @ 0x02216b34, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *ptr);
extern int func_02008258(void *self, int value);
extern void func_0200d4e8(void *self, int a, int b, int c);

typedef struct UnkStruct_02216b34 {
    char pad_00[0x2d0];
    int unk_2D0;
    char pad_2D4[0x7f0 - 0x2d0 - 4];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    int unk_7FC;
} UnkStruct_02216b34;

void func_ov003_02216b34(UnkStruct_02216b34 *self)
{
    if (func_02056f94(&self->unk_2D0) != 0) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        func_0200d4e8(self, 3, 1, -1);
    }
}

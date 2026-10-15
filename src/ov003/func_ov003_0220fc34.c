/* func_ov003_0220fc34 @ 0x0220fc34, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *);
extern unsigned int func_02008258(void *, unsigned int);
extern int func_0200d4e8(void *, int, int, int);
extern int func_ov003_0220d268(void *);

typedef struct UnkStruct_0220fc34 {
    char pad_first[0x2d0];
    char unk_2D0[8];
    unsigned int unk_2D8;
    char pad_2DC[0x7f0 - 0x2d8 - 4];
    unsigned int unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    unsigned int unk_7FC;
} UnkStruct_0220fc34;

void func_ov003_0220fc34(UnkStruct_0220fc34 *self)
{
    if (func_02056f94(self->unk_2D0)) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        func_0200d4e8(self, 3, 1, -1);
    }
    if (((self->unk_2D8 << 4) >> 16) >= 22) {
        func_ov003_0220d268(self);
    }
}

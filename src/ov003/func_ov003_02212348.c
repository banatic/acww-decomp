/* func_ov003_02212348 @ 0x02212348, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *);
extern int func_02008258(void *, int);
extern void func_0200d4e8(void *, int, int, int);

struct UnkStruct_02212348 {
    char pad_00[0x2d0];
    int unk_2D0;
    char pad_2D4[0x51c];
    int unk_7F0;
    char pad_7F4[0x8];
    int unk_7FC;
};

void func_ov003_02212348(struct UnkStruct_02212348 *self)
{
    if (func_02056f94(&self->unk_2D0)) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        func_0200d4e8(self, 3, 1, -1);
    }
}

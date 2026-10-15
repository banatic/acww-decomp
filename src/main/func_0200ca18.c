/* func_0200ca18 @ 0x0200ca18, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0200ca18 {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[8];
    int unk_98;
    char pad_9C[0x738];
    short unk_7D4;
    char pad_7D6[0x1a];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
};

extern int func_02008258(struct UnkStruct_0200ca18 *self, int arg);
extern int func_0200d4e8(struct UnkStruct_0200ca18 *self, int a, int b, int c);

void func_0200ca18(struct UnkStruct_0200ca18 *self)
{
    int c = self->unk_98;
    if (self->unk_8E != self->unk_7D4) {
        return;
    }
    if (c > 0) {
        return;
    }
    self->unk_7FC = func_02008258(self, self->unk_7F0);
    func_0200d4e8(self, 3, 1, -1);
}

/* func_020bb35c @ 0x020bb35c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x120c];
    int unk_120C;
    char pad_1210[0x1524 - 0x1210];
    int unk_1524;
    char pad_1528[0x152c - 0x1528];
    int unk_152C;
    char pad_1530[0x158c - 0x1530];
    int unk_158C;
    int unk_1590;
} UnkStruct_020bb35c;

extern void func_020bb7e0(UnkStruct_020bb35c *self, int a, int c);

void func_020bb35c(UnkStruct_020bb35c *self)
{
    int a = self->unk_1524;
    int b = self->unk_152C;
    int c;
    if (b > a) {
        c = a + 1;
    } else {
        c = a - 1;
    }
    func_020bb7e0(self, a, c);
    self->unk_120C = 0;
    self->unk_158C = 2;
    self->unk_1590 = 0;
}

/* func_020bb3f4 @ 0x020bb3f4, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02002b40(void *p, int a, int b, int c);

typedef struct {
    char pad_00[0x1208];
    int unk_1208;
    char pad_120C[0x1520 - 0x120c];
    int unk_1520;
    int unk_1524;
    char pad_1528[0x152c - 0x1528];
    int unk_152C;
    int unk_1530;
    char pad_1534[0x1578 - 0x1534];
    int unk_1578;
    char *unk_157C;
    char pad_1580[0x158c - 0x1580];
    int unk_158C;
} UnkStruct_020bb3f4;

void func_020bb3f4(UnkStruct_020bb3f4 *self)
{
    int idx = self->unk_1578;
    int comp = (((self->unk_1208 >> 8) - 8) & 0xff) >> 3;
    if (comp != idx) {
        return;
    }
    if (func_02002b40(self->unk_157C + comp * 32, 6, 0x20, comp * 32) == 0) {
        return;
    }
    idx++;
    if (idx >= 0x20) {
        idx = -1;
        if (self->unk_152C == self->unk_1524) {
            self->unk_158C = 0;
            self->unk_152C = -1;
            self->unk_1530 = 2;
            self->unk_1520 = 0;
        } else {
            self->unk_158C = 1;
        }
    }
    self->unk_1578 = idx;
}

/* func_020bb480 @ 0x020bb480, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020bb66c(void *self, int a, int b);
extern int func_020bb608(void *self, int *p1, int *p2, int a, int b);

struct UnkStruct_020bb480 {
    char pad_00[0x120c];
    int unk_120C;
    char pad_1210[0x314];
    int unk_1524;
    char pad_1528[0x50];
    int unk_1578;
    int unk_157C;
    int unk_1580;
    char pad_1584[0x8];
    int unk_158C;
};

void func_020bb480(struct UnkStruct_020bb480 *self)
{
    int val = self->unk_1524;
    if (func_020bb66c(self, val, 6)) {
        if (func_020bb608(self, &self->unk_157C, &self->unk_1580, 0, val)) {
            self->unk_1578 = 0;
            self->unk_120C = 0x20;
            self->unk_158C = 4;
        }
    }
}

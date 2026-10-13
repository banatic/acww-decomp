/* func_020bb75c @ 0x020bb75c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x1520];
    int unk_1520;
    int unk_1524;
    char pad_1528[0x158c - 0x1528];
    int unk_158C;
} UnkStruct_020bb75c;

extern void func_020bb7a0(UnkStruct_020bb75c *self, int value);

int func_020bb75c(UnkStruct_020bb75c *self, int value)
{
    int flag = 0;

    if (value == -1) {
        goto end;
    }
    if (value == self->unk_1524) {
        flag = 1;
        goto end;
    }
    if (self->unk_1520 != 0) {
        goto end;
    }

    func_020bb7a0(self, value);
    flag = 1;
    self->unk_158C = flag;
    self->unk_1520 = flag;

end:
    return flag;
}

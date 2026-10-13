/* func_02034310 @ 0x02034310, 0xe0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02034448(void *ptr, int x, int y, int value);

typedef struct {
    unsigned char pad_00[0x498];
    int unk_498;
    int unk_49C;
    int unk_4A0;
    int unk_4A4;
} UnkStruct_02034310;

void func_02034310(UnkStruct_02034310 *self, int x0, int x1, int y0, int y1, int value)
{
    int width = x1 - x0 + 1;
    int height = y1 - y0 + 1;
    int row, col;

    if (width <= 7 && height <= 7) {
        self->unk_498 = x0;
        self->unk_49C = x1;
        self->unk_4A0 = y0;
        self->unk_4A4 = y1;
        row = self->unk_4A0;
        while (row <= self->unk_4A4) {
            col = self->unk_498;
            while (col <= self->unk_49C) {
                func_02034448((char *) self + (row - self->unk_4A0) * 0xa8 + (col - self->unk_498) * 0x18, col, row, value);
                col++;
            }
            row++;
        }
    } else {
        self->unk_498 = x0;
        self->unk_49C = x0 + 6;
        self->unk_4A0 = y0;
        self->unk_4A4 = y0 + 6;
        row = self->unk_4A0;
        while (row <= self->unk_4A4) {
            col = self->unk_498;
            while (col <= self->unk_49C) {
                func_02034448((char *) self + (row - self->unk_4A0) * 0xa8 + (col - self->unk_498) * 0x18, col, row, value);
                col++;
            }
            row++;
        }
    }
}

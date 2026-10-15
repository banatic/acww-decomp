/* func_ov003_022154ec @ 0x022154ec, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *ptr);
extern int func_02008258(void *self, int val);
extern int func_02008c40(void *self, int a, int b);
extern int func_0200d4e8(void *self, int a, int b, int c);

typedef struct {
    char pad_00[0x2d0];
    char unk_2D0;
    char pad_2D1[0x7d4 - 0x2d0 - 1];
    unsigned char unk_7D4;
    char pad_7D5[0x7f0 - 0x7d4 - 1];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    int unk_7FC;
} MrPeanut;

int func_ov003_022154ec(MrPeanut *self)
{
    int result = func_02056f94(&self->unk_2D0);
    if (result == 0) {
        return result;
    }
    self->unk_7FC = func_02008258(self, self->unk_7F0);
    if (self->unk_7D4 != 0) {
        return func_02008c40(self, 5, -1);
    } else {
        return func_0200d4e8(self, 3, 1, -1);
    }
}

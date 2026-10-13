/* func_ov003_02217a38 @ 0x02217a38, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200f268(void *, int);

typedef struct {
    char pad_00[0x5a4];
    unsigned int unk_5A4;
    char pad_5A8[0x23e];
    unsigned char unk_7E6;
} UnkStruct_02217a38;

void func_ov003_02217a38(UnkStruct_02217a38 *self)
{
    if ((self->unk_7E6 & 3) == 2) {
        self->unk_5A4 = 0x1000;
    } else {
        self->unk_5A4 = 0;
        func_0200f268(self, 0);
    }
}

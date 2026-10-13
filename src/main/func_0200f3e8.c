/* func_0200f3e8 @ 0x0200f3e8, 0x4a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[4];
    int unk_64;
    char pad_68[0x26];
    short unk_8E;
} UnkStruct_0200f3e8;

extern unsigned int func_02064558(int x);

void func_0200f3e8(UnkStruct_0200f3e8 *self)
{
    unsigned int v = func_02064558(self->unk_8E);
    switch (v) {
        case 2:
            self->unk_64--;
            break;
        case 0:
            self->unk_64++;
            break;
        case 3:
            self->unk_5C--;
            break;
        case 1:
            self->unk_5C++;
            break;
    }
}

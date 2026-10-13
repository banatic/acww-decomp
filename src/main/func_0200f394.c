/* func_0200f394 @ 0x0200f394, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064558(int);

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[0x4];
    int unk_64;
    char pad_68[0x26];
    short unk_8E;
    char pad_90[0x770];
    int unk_800;
} Self0300f394;

void func_0200f394(Self0300f394 *self)
{
    int dir;
    int delta;

    dir = func_02064558(self->unk_8E);
    delta = self->unk_800;

    switch (dir) {
        case 2:
            self->unk_64 -= delta;
            break;
        case 0:
            self->unk_64 += delta;
            break;
        case 3:
            self->unk_5C -= delta;
            break;
        case 1:
            self->unk_5C += delta;
            break;
    }
}

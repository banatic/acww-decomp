/* func_020c003c @ 0x020c003c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020c003c {
    char pad_00[0xc];
    int unk_0C;
    char pad_10[0x48];
    int unk_58;
    char pad_5C[4];
    int unk_60;
    int unk_64;
    int unk_68;
} UnkStruct_020c003c;

extern void func_020bff20(UnkStruct_020c003c *, int);
extern void func_020bffc4(UnkStruct_020c003c *, int);

void func_020c003c(UnkStruct_020c003c *self, int a)
{
    int kind;
    unsigned int ok;

    kind = (a & 0xf) + 0x1d;
    self->unk_0C = kind;
    self->unk_58 = 2;
    self->unk_60 = a;
    ok = 0;
    self->unk_64 = ok;
    self->unk_68 = ok;
    kind -= 0x21;
    if ((unsigned int) kind <= 9) {
        if (((1 << kind) & 0x249) != 0) {
            ok = 1;
        }
    }
    if (ok != 0) {
        func_020bff20(self, a);
    } else {
        func_020bffc4(self, a);
    }
}

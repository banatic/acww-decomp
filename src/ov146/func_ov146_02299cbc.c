/* func_ov146_02299cbc @ 0x02299cbc, 0x48 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02299cbc {
    int pad_00;
} UnkStruct_02299cbc;

typedef struct UnkStruct_02299cbc_2 {
    char pad_00[0x98];
    int unk_98;
    int unk_9C;
    int unk_A0;
    char pad_A4[0x1F10];
    UnkStruct_02299cbc sub;
} UnkStruct_02299cbc_2;

extern int func_ov002_0220a58c(UnkStruct_02299cbc *, int arg1, int arg2);
extern void func_ov002_0220a574(UnkStruct_02299cbc *);

int func_ov146_02299cbc(UnkStruct_02299cbc_2 *self, int unused, int value)
{
    if (func_ov002_0220a58c(&self->sub, unused, value)) {
        self->unk_9C = self->unk_98 - value;
        func_ov002_0220a574(&self->sub);
        self->unk_A0 = self->unk_98;
        return 1;
    } else {
        return 0;
    }
}

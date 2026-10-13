/* func_ov142_02299c1c @ 0x02299c1c, 0x48 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a58c(void *p);
extern void func_ov002_0220a574(void *p);

struct UnkStruct_02299c1c {
    char pad_00[0xa8];
    int unk_A8;
    int unk_AC;
    int unk_B0;
};

int func_ov142_02299c1c(struct UnkStruct_02299c1c *self, int unused, int value)
{
    if (func_ov002_0220a58c((char *) self + 0x14c) != 0) {
        self->unk_AC = self->unk_A8 - value;
        func_ov002_0220a574((char *) self + 0x14c);
        self->unk_B0 = self->unk_A8;
        return 1;
    }
    return 0;
}

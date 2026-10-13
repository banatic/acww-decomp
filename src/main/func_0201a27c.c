/* func_0201a27c @ 0x0201a27c, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201a27c;
extern int func_0201a2e8(struct UnkStruct_0201a27c *, int);
extern void func_0201a2d4(struct UnkStruct_0201a27c *);
extern int func_0201a2c8(struct UnkStruct_0201a27c *, int *);

struct UnkStruct_0201a27c {
    char pad_00[0x50];
    int unk_50;
    char pad_54[0x24];
    int unk_78;
    int pad_7C;
    int *unk_80;
};

void func_0201a27c(struct UnkStruct_0201a27c *self)
{
    if (func_0201a2e8(self, self->unk_78)) {
        func_0201a2d4(self);
        self->unk_50 = func_0201a2c8(self, self->unk_80) << 12;
    }
}

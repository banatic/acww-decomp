/* func_ov002_0220823c @ 0x0220823c, 0x30 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ee61c(void *);
extern void func_ov002_02208880(void *, int, int, int);

typedef struct UnkStruct_0220823c {
    char pad_00[8];
    int unk_08;
    char pad_0C[0x6C - 0x0C];
    struct UnkStruct_0220823c *unk_6C;
    char pad_70[0x90 - 0x70];
    unsigned char unk_90;
} UnkStruct_0220823c;

int func_ov002_0220823c(UnkStruct_0220823c *self)
{
    if (!func_020ee61c(self)) {
        return 0;
    }
    self->unk_90 = self->unk_08;
    self->unk_6C = self;
    self = (UnkStruct_0220823c *) ((char *) self + 0x50);
    func_ov002_02208880(self, 8, 1, 7);
    return 1;
}

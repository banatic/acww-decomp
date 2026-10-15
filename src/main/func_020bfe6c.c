/* func_020bfe6c @ 0x020bfe6c, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a160(void *);
extern void func_020c00fc(void *);
extern void func_020c0084(void *, int);
extern void func_020c0324(void *out, int px, int py, int flag);
extern void func_020c013c(void *);
extern unsigned int data_020d2eec;

struct UnkStruct_020bfe6c {
    char pad_00[0x4];
    int unk_04;
    char pad_08[0x8];
    char sub_10[0x24];
    char unk_34[0x2c];
    unsigned int flags;
    int unk_64;
    char pad_68[0x4];
    unsigned int unk_6C;
    unsigned int unk_70;
};

void func_020bfe6c(struct UnkStruct_020bfe6c *self)
{
    unsigned int flags = self->flags;
    int r4 = ((flags >> 30) & 1) ? 0 : 1;
    int r6 = ((flags >> 31) & 1) ? 1 : 0;

    if (func_0208a160(self->sub_10) != 0) {
        if (r4 != 0) {
            func_020c00fc(self);
        }
        self->unk_04 = 3;
    } else {
        func_020c0084(self, -1);
        func_020c0324(self->unk_34, self->unk_6C, self->unk_70, r6);
        if (r4 != 0) {
            func_020c013c(self);
        }
    }

    if (self->unk_64 == 0x1d) {
        self->flags |= data_020d2eec;
    }
}

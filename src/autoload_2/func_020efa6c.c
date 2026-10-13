/* func_020efa6c @ 0x020efa6c, 0xc8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void OS_Terminate(void);

struct UnkStruct_020efa6c {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned int unk_18;
    unsigned int unk_1C;
};

extern unsigned int (*data_021fd19c)(struct UnkStruct_020efa6c *);
extern unsigned int (*data_021fd1a4)(struct UnkStruct_020efa6c *);
extern unsigned int (*data_021fd1a0)(struct UnkStruct_020efa6c *);

void func_020efa6c(struct UnkStruct_020efa6c *self)
{
    if (self->unk_04 == 0) {
        self->unk_10 = 0;
        self->unk_14 = 0x7f;
        self->unk_1C = 0x7f;
        self->unk_18 = 0;
        return;
    }

    if (data_021fd19c == 0) {
        OS_Terminate();
    }
    if (data_021fd1a4 == 0) {
        OS_Terminate();
    }
    if (data_021fd1a0 == 0) {
        OS_Terminate();
    }

    self->unk_10 = data_021fd19c(self);
    self->unk_14 = data_021fd1a4(self);
    self->unk_1C = self->unk_14;
    self->unk_18 = data_021fd1a0(self);
    return;
}

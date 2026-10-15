/* func_ov095_02299aec @ 0x02299aec, 0x44 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299aec {
    unsigned char pad_00[0x16];
    unsigned char unk_16;
    unsigned char pad_17[0x11];
    int unk_28;
};

extern void func_ov095_0229ab68(void *unused0);
extern void func_ov095_0229aae0(void *unused0);
extern void func_ov095_0229aaac(void *unused0);

void func_ov095_02299aec(struct UnkStruct_02299aec *self)
{
    switch (self->unk_16) {
        case 0:
            break;
        case 1:
            self->unk_28 = 0x3b;
            func_ov095_0229ab68(self);
            break;
        case 2:
            self->unk_28 = 0x70;
            func_ov095_0229aae0(self);
            break;
        case 3:
            break;
        case 4:
            self->unk_28 = 0xc9;
            func_ov095_0229aaac(self);
            break;
    }
}

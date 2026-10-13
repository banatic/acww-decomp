/* func_ov003_0221bd38 @ 0x0221bd38, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221bd38 {
    int unk_00;
    int unk_04;
};

struct UnkStruct_0221bd38_2 {
    unsigned char pad_00[0xec];
    int unk_EC;
    unsigned char pad_F0[0x3c];
    struct UnkStruct_0221bd38 *unk_12C;
};

extern void func_0203ee08(void *self, void *arg);
extern void func_0203e020(void *self);

void func_ov003_0221bd38(struct UnkStruct_0221bd38_2 *self)
{
    if (self->unk_12C && self->unk_12C->unk_04 == 0) {
        void *arg = (void *) self;
        if (self) {
            arg = (char *) self + 0xec;
        }
        func_0203ee08(self, arg);
        func_0203e020(self);
    }
}

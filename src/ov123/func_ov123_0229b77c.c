/* func_ov123_0229b77c @ 0x0229b77c, 0x3c bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229b77c {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[23];
    unsigned char unk_A5;
    unsigned char pad_A6[4];
    unsigned char unk_AA;
    unsigned char pad_AB[289];
    char unk_1CC;
};

extern int func_0208e484(void *p);
extern void func_ov123_0229ae84(struct UnkStruct_0229b77c *self);
extern void func_ov123_02299ca0(struct UnkStruct_0229b77c *self);

void func_ov123_0229b77c(struct UnkStruct_0229b77c *self)
{
    if (func_0208e484(&self->unk_1CC)) {
        self->unk_A5 = self->unk_AA;
        func_ov123_0229ae84(self);
        if (self->unk_8D == 0xa) {
            func_ov123_02299ca0(self);
        }
    }
}

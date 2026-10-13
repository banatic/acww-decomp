/* func_02003428 @ 0x02003428, 0xe8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffd41c(void);
extern int FX_MulFunc(int, int);
extern int func_0203a7b8(void *, void *, int *, int, void *);
extern short FX_SinCosTable_[];
struct UnkStruct_02003428 {
    unsigned char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned int unk_60;
    unsigned int unk_64;
    unsigned int unk_68;
    unsigned int unk_6C;
    unsigned int unk_70;
    unsigned int unk_74;
    unsigned char pad_78[0xb0 - 0x78];
    unsigned int unk_B0;
    unsigned int unk_B4;
    unsigned int unk_B8;
    unsigned int unk_BC;
    unsigned char pad_C0[0xc4 - 0xc0];
    unsigned int unk_C4;
    unsigned int unk_C8;
    unsigned int unk_CC;
    unsigned short unk_D0;
};
extern unsigned char data_0213fee4[];
extern unsigned char data_021f6a6c[];

int func_02003428(struct UnkStruct_02003428 *self)
{
    int r4_var;
    int val;
    if (func_01ffd41c() == 0) {
        return 0;
    }
    self->unk_68 = self->unk_5C;
    self->unk_6C = self->unk_60;
    self->unk_70 = self->unk_64;
    if (((((self->unk_B8 != 0))))) {
        int val1 = FX_MulFunc(self->unk_B4, FX_SinCosTable_[(self->unk_D0 >> 4) * 2]);
        r4_var = self->unk_CC + val1;
        {
            int val2 = FX_MulFunc(self->unk_B4, FX_SinCosTable_[((self->unk_D0 >> 4) * 2) + 1]);
            int triplet[3];
            val = self->unk_C8 + val2;
            triplet[0] = self->unk_C4;
            triplet[1] = val;
            triplet[2] = r4_var;
            r4_var = func_0203a7b8((void *) data_021f6a6c, (void *) data_0213fee4, triplet, self->unk_B8, &self->unk_74);
        }
    }
    self->unk_B0 &= ~4u;
    if ((self->unk_B0 & 3u) == 0) {
        goto ret1;
    }
    if (r4_var <= ((int) self->unk_BC)) {
        goto ret1;
    }
    self->unk_B0 |= 4u;
    if ((self->unk_B0 & 1u) == 0) {
        goto ret1;
    }
    return 0;
ret1:
    return 1;
}

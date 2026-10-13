/* func_0203a89c @ 0x0203a89c, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int, int);
extern int FX_MulFunc(int, int);
extern void VEC_CrossProduct(int *, int *, int *);
extern void VEC_Normalize(int *, int *);

extern short FX_SinCosTable_[];

struct UnkStruct_0203a89c {
    int pad_00;
    int unk_04[3];
    int unk_10[3];
    int unk_1C[3];
    int unk_28[3];
    int pad_34[6];
    int unk_4C;
    int unk_50;
    int pad_54;
    unsigned short unk_58;
};

void func_0203a89c(struct UnkStruct_0203a89c *self)
{
    int i = self->unk_58 >> 4;
    int t1 = FX_Div(FX_SinCosTable_[i * 2], FX_SinCosTable_[i * 2 + 1]);
    int t2 = FX_MulFunc(self->unk_50, t1);
    int t3 = FX_MulFunc(self->unk_4C, t2);
    int buf[12];

    buf[0] = -t3;
    buf[1] = -t2;
    buf[2] = -self->unk_50;
    buf[3] = -t3;
    buf[4] = t2;
    buf[5] = -self->unk_50;
    buf[6] = t3;
    buf[7] = t2;
    buf[8] = -self->unk_50;
    buf[9] = t3;
    buf[10] = -t2;
    buf[11] = -self->unk_50;

    VEC_CrossProduct(&buf[3], &buf[0], self->unk_04);
    VEC_CrossProduct(&buf[6], &buf[3], self->unk_10);
    VEC_CrossProduct(&buf[9], &buf[6], self->unk_1C);
    VEC_CrossProduct(&buf[0], &buf[9], self->unk_28);

    VEC_Normalize(self->unk_04, self->unk_04);
    VEC_Normalize(self->unk_10, self->unk_10);
    VEC_Normalize(self->unk_1C, self->unk_1C);
    VEC_Normalize(self->unk_28, self->unk_28);
}

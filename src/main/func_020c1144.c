/* func_020c1144 @ 0x020c1144, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern int func_020be0d4(int, int);
extern int FX_Div(int, int);
extern int FX_MulFunc(int, int);
extern short FX_SinCosTable_[];
struct Entry {
    char pad_00[4];
    int unk_04;
    char pad_08[0x34 - 0x8];
    int unk_34;
    int unk_38;
    char pad_3C[0x50 - 0x3c];
    int unk_50;
    unsigned short unk_54;
    char pad_56[0x74 - 0x56];
};
extern struct Entry data_021f8b48[];
struct UnkStruct_020c1144 {
    int unk_00;
    int unk_04;
    char pad_08[8];
    int unk_10;
    char pad_14[32];
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    int unk_50;
    unsigned short unk_54;
    char pad_56[10];
    unsigned int unk_60;
    int unk_64;
};
struct Vec {
    int x;
    int y;
    int z;
};
int func_020c1144(struct UnkStruct_020c1144 *self)
{
    int t;
    struct Entry *e;
    struct Vec *ep;
    int div;
    int new38;
    int *sp;
    int val;
    int result;
    volatile int dbg[4];
    volatile int *dp = dbg;

    e = &data_021f8b48[func_020be0d4((int) data_021f8b48, 3)];
    result = 0;
    if (e != 0 && e->unk_04 == 2) {
        ep = (struct Vec *) &e->unk_34;
        t = ((unsigned short) (short) e->unk_54 >> 4) * 2;
        div = FX_Div(0x10000, e->unk_50);
        new38 = ep->y + FX_MulFunc(FX_SinCosTable_[t + 1], div);
        val = e->unk_34 - FX_MulFunc(FX_SinCosTable_[t], div);
        sp = &self->unk_34;
        *sp = val;
        *(sp + 1) = new38;
        *(sp + 2) = 0;
        result = 1;
    }
    return result;
}

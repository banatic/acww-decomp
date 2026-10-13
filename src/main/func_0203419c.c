/* func_0203419c @ 0x0203419c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int, int);
extern int FX_MulFunc(int, int);

typedef struct {
    char pad_00[0x34];
    int unk_34;
    char pad_38[0x04];
    int unk_3C;
} UnkStruct_0203419c;

int func_0203419c(UnkStruct_0203419c *p)
{
    if (p->unk_34 == 0x16) {
        return FX_MulFunc(p->unk_3C, FX_Div(0x1e000, 0x64000));
    } else {
        return p->unk_3C;
    }
}

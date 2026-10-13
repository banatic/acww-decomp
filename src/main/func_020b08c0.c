/* func_020b08c0 @ 0x020b08c0, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int, int);
extern int FX_MulFunc(int, int);

typedef struct {
    unsigned char pad_00;
    unsigned char pad_01;
    unsigned short lowbit : 7;
    unsigned short fieldbit : 7;
    unsigned char type;
} UnkStruct_020b08c0;

int func_020b08c0(UnkStruct_020b08c0 *p)
{
    int r4;
    int r1;

    r4 = p->fieldbit << 7;
    if (r4 == 0) {
        r4 = 0x1000;
    }

    r1 = 0x1000;
    if (p->type == 1) {
        r1 = FX_Div(0x3000, 0x4000);
    } else if (p->type == 2) {
        r1 = FX_Div(0x1000, 0x2000);
    }

    if (r1 > 0x1000) {
        r1 = 0x1000;
    }

    return FX_MulFunc(r4, r1);
}

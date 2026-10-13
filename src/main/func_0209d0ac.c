/* func_0209d0ac @ 0x0209d0ac, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x34];
    unsigned char flag;
    char pad_35[3];
    unsigned int value;
} UnkStruct_0209d0ac;

extern int func_0209d320(unsigned int);
extern int func_0209d324(unsigned int);
extern int func_020559d0(UnkStruct_0209d0ac *, unsigned int, int, int, unsigned int);
extern unsigned int data_021fbe94;

unsigned char func_0209d0ac(UnkStruct_0209d0ac *P, unsigned int X, unsigned int Y)
{
    if (P->value == 0) {
        P->value = X;
    }
    if (P->flag != 0) {
        goto exit;
    }
    {
        int v1 = func_0209d320(X);
        int v2 = func_0209d324(X);
        if (func_020559d0(P, Y, v1, v2, data_021fbe94) == 3) {
            P->flag = 1;
        }
    }
exit:
    return P->flag;
}

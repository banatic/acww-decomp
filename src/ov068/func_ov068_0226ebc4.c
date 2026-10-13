/* func_ov068_0226ebc4 @ 0x0226ebc4, 0x90 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int, int);
extern void func_ov068_0226fcbc(void *);
extern void func_020ee470(void *);
extern short FX_SinCosTable_[];

void func_ov068_0226ebc4(char *a0)
{
    short cos;

    *(int *) (a0 + 0x270) = *(int *) (a0 + 0x26c);
    cos = FX_SinCosTable_[(*(unsigned short *) (a0 + 0x396) >> 4) * 2 + 1];
    *(int *) (a0 + 0x308) = FX_MulFunc(0x100, cos);
    *(int *) (a0 + 0x310) = -FX_MulFunc(0x100, cos);
    *(unsigned short *) (a0 + 0x396) = *(short *) (a0 + 0x396) + 0x5000;
    if (*(unsigned char *) (a0 + 0x398) != 0) {
        *(unsigned char *) (a0 + 0x398) -= 1;
    }
    if (*(unsigned char *) (a0 + 0x398) == 0) {
        func_ov068_0226fcbc(a0);
        func_020ee470(a0);
    }
}

/* func_ov004_02240f2c @ 0x02240f2c, 0x94 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int a, int b);

int func_ov004_02240f2c(void *self, short a, int b, short c, short d, int e, int f)
{
    int valueResult;

    int *src = (int *) ((char *) self + 0x2c8);
    int *dst = (int *) ((char *) self + 0x34);

    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    *(short *) ((char *) self + 0x172) = 0x19;
    *(short *) ((char *) self + 0x192) = d;
    *(short *) ((char *) self + 0x190) = c;
    *(short *) ((char *) self + 0x9e) = a;
    *(int *) ((char *) self + 0xa0) = FX_MulFunc(b << 12, 0x100);
    *(int *) ((char *) self + 0x4c) = 0;
    *(int *) ((char *) self + 0x16c) = f;
    *(short *) ((char *) self + 0x30) = 0;
    *(short *) ((char *) self + 0x9c) = 0;
    *(int *) ((char *) self + 0xa8) = src[1] + FX_MulFunc(e << 12, 0x100);
    *(int *) ((char *) self + 0x54) = *(int *) ((char *) self + 0xa8);
    valueResult = 0;
    *((char *) self + 0x9a) = valueResult;
    return valueResult;
}

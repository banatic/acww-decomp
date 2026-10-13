/* func_ov003_0222e898 @ 0x0222e898, 0xd8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov003_02260e4c[];
extern short FX_SinCosTable_[];
extern int FX_MulFunc(int a, int b);
extern char *func_020961a8(int idx);

void func_ov003_0222e898(int type, int idx)
{
    unsigned char *p;
    char *src;
    int *d;
    int *q;
    int k;
    int a;

    p = data_ov003_02260e4c + idx * 0x25c;
    src = func_020961a8(idx);
    if (src != 0) {
        q = (int *) (src + 0x5c);
        d = (int *) (p + 0x204);
        d[0] = q[0];
        d[1] = q[1];
        d[2] = q[2];
        d[1] += 0x1b34;
        a = *(short *) (src + 0x8e);
        *(short *) (p + 0x23a) = (short) a;
        k = ((unsigned short) a >> 4) << 1;
        *(int *) (p + 0x204) += FX_MulFunc(0xfae, FX_SinCosTable_[k]);
        d[2] += FX_MulFunc(0xfae, FX_SinCosTable_[k + 1]);
    }
    p[0x250] = 1;
    p[0x251] = 0x10;
    switch (type) {
        case 0x25:
            p[0x24d] = 0x39;
            break;
        case 0x3a:
            p[0x24d] = 0xb;
            break;
        case 0x3b:
            p[0x24d] = 0x18;
            break;
        default:
            p[0x24d] = (unsigned char) type;
            break;
    }
}

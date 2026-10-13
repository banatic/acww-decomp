/* func_020b3438 @ 0x020b3438, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct _S {
    unsigned char pad_00[0x18];
    unsigned char count;
};

extern int func_020b3428(int a);
extern int func_020b365c(int a, int b, int c);
extern int func_020b34e0(void *a, int b);
extern int NNSi_G3dModifyMatFlag(struct _S *a, int b, int c);
extern void NNS_G3dMdlSetMdlEmi(struct _S *a, int b, int c);

void func_020b3438(void *arg0, struct _S *arg1, int arg2)
{
    int i;
    int v6;
    int v7;
    int v8;
    int v9;
    int v10;
    int value;

    if (arg2 != 0) {
        v6 = func_020b3428(NNSi_G3dModifyMatFlag(arg1, 1, 0x400));

        v7 = func_020b365c(arg2, ((v6 >> 10) & 0x1f) << 12, 0x1f000);
        v8 = func_020b365c(arg2, (v6 & 0x1f) << 12, 0x1f000);
        v9 = func_020b365c(arg2, ((v6 >> 5) & 0x1f) << 12, 0x1f000);

        v10 = ((v7 >> 12) << 10) | ((v8 >> 12) | ((v9 >> 12) << 5));
        v7 = (unsigned short) v10;

        for (i = 0; i < arg1->count; i++) {
            if (func_020b34e0(arg0, i) != 0) {
                value = v7;
            } else {
                value = v6;
            }
            NNS_G3dMdlSetMdlEmi(arg1, i, value);
        }
    } else {
        NNSi_G3dModifyMatFlag(arg1, 0, 0x400);
    }
}

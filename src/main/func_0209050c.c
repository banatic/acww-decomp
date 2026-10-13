/* func_0209050c @ 0x0209050c, 0x12c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02090638(void *, int);
extern void func_02055478(void *, int);
extern void func_02055140(void *, int);
extern void func_02055060(void *, int, int, int, int, int);
extern void func_02055050(void *);
extern void func_0205650c(void *, int, int);
extern void func_02056478(void *, int, int, int, int);
extern int func_02055e00(void *);
extern void func_020563dc(void *, int);
extern void func_020564d0(void *, int, int);

extern int NNS_G3dGetJntAnmSet(int);
extern int func_02107b44(int, int);
extern int NNS_G3dGetMatCAnmSet(int);
extern int func_02107b80(int, int);
extern int NNS_G3dGetVisAnmSet(int);
extern int func_02107cf0(int, int);

extern int data_021d52c8;

void func_0209050c(unsigned int *param0, unsigned int *param1)
{
    int tmp;
    unsigned int *p;
    unsigned int *r6;
    const unsigned int size = 0x1000;

    tmp = *param1;
    *param0 = 0;
    if (func_02090638(param0, tmp) == 0) {
        return;
    }

    p = (unsigned int *) ((char *) param1 + 0x524);

    if (*p != 0) {
        func_02055478((char *) param0 + 0x24, data_021d52c8);
        func_02055140((char *) param0 + 0x24, data_021d52c8);
        tmp = NNS_G3dGetJntAnmSet(*p);
        tmp = func_02107b44(tmp, 0);
        func_02055060((char *) param0 + 0x24, tmp, 1, size, 0, 0);
        func_02055050((char *) param0 + 0x24);
    }

    if (p[1] != 0) {
        *(unsigned int *) ((char *) param0 + 0xe0) = 1;
        r6 = (unsigned int *) ((char *) param0 + 0x108);
        func_0205650c(r6, *(unsigned int *) ((char *) param0 + 0x80), data_021d52c8);
        tmp = NNS_G3dGetMatCAnmSet(p[1]);
        tmp = func_02107b80(tmp, 0);
        func_02056478(r6, tmp, 1, size, 0);
        func_020563dc(r6, func_02055e00((char *) param0 + 0x24));
    } else {
        *(unsigned int *) ((char *) param0 + 0xe0) = 0;
    }

    if (p[2] != 0) {
        *(unsigned int *) ((char *) param0 + 0xe4) = 1;
        r6 = (unsigned int *) ((char *) param0 + 0x128);
        func_020564d0(r6, *(unsigned int *) ((char *) param0 + 0x80), data_021d52c8);
        tmp = NNS_G3dGetVisAnmSet(p[2]);
        tmp = func_02107cf0(tmp, 0);
        func_02056478(r6, tmp, 1, size, 0);
        func_020563dc(r6, func_02055e00((char *) param0 + 0x24));
    } else {
        *(unsigned int *) ((char *) param0 + 0xe4) = 0;
    }
}
/* func_02010a24 @ 0x02010a24, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020110b4(void *self, int *out);
extern void func_0205cc1c(void *ptr, int a, int b, int c);
extern int func_0205cb94(void *ptr);
extern int NNS_G3dGetJntAnmSet(void *resource);
extern int func_02107b44(int a, int b);
extern void func_02054828(void *dst, int a, int b, unsigned char c, int d, int e, int f);
extern void func_020108cc(void *self, int a, unsigned short b);
extern void func_02010bf0(void *self, int *a, unsigned char *b);
extern void func_02010bac(void *self, int *a, unsigned char *b);

void func_02010a24(void *self, int p1, int p2, unsigned char p3, int p4, unsigned short p5, unsigned short p6, int p7)
{
    int localResult;
    int r6 = *(int *) ((char *) self + 0x704);

    if (r6 == 0xa1) {
        p2 = 0;
        p6 = 0;
    }

    if (p7 < 0x137) {
        localResult = p7;
    } else {
        localResult = func_020110b4(self, &p1);
    }

    if (p1 != 0 || r6 != 0 || p5 != 0 || p2 == 0 || p7 < 0x137) {
        func_0205cc1c((char *) self + 0x700, localResult, 1, 0);
        {
            int tmp = NNS_G3dGetJntAnmSet((void *) func_0205cb94((char *) self + 0x700));
            int ret = func_02107b44(tmp, 0);
            func_02054828((char *) self + 0x234, ret, p2, p3, p4, p5, 0);
        }
        *(int *) ((char *) self + 0x704) = p1;
        *((char *) self + 0x70c) = p3;
    }

    func_020108cc(self, localResult, p6);
    func_02010bf0(self, &localResult, &p3);
    func_02010bac(self, &localResult, &p3);
}

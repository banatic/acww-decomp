/* func_ov004_022225fc @ 0x022225fc, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern void *func_0206fc8c(void);
extern void func_0209a050(void *h);
extern int func_020644cc(int k);
extern void func_0206844c(void *a, void *b, int c);
extern void func_ov004_02222178(void *p, int k);
extern void func_02015330(void *self, void *obj, int a, int b, int c);

void func_ov004_022225fc(void *self)
{
    unsigned char b[4];

    if (*(int *) ((char *) *(void **) ((char *) self + 0x1a8) + 0x89c) == 6 && func_0206fbc0() != 0) {
        if (func_0206fc6c() == 0) {
            *(int *) ((char *) *(void **) ((char *) self + 0x40) + 8) = 1;
            b[0] = (unsigned char) (func_020644cc(3) + 0xd);
            func_0206844c(*(void **) ((char *) self + 0x40), &b[0], 0);
            func_ov004_02222178(*(void **) ((char *) self + 0x1a8), 4);
        } else {
            func_0209a050(func_0206fc8c());
            b[1] = (unsigned char) (func_020644cc(3) + 0x10);
            func_0206844c(*(void **) ((char *) self + 0x40), &b[1], 0);
            *(short *) (b + 2) = 0x155e;
            func_02015330(self, b + 2, 0, 6, 0);
            func_ov004_02222178(*(void **) ((char *) self + 0x1a8), 7);
        }
    }
}

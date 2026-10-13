/* func_ov004_0221cd68 @ 0x0221cd68, 0x144 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern void *func_0206fc8c(void);
extern int func_020644cc(int k);
extern void func_0206844c(void *a, void *b, int c);
extern void func_ov004_0221c844(void *p, int k);
extern int func_0209a034(void *h);
extern int func_0204c878(void *obj);
extern void func_0209a050(void *h);
extern void func_02015de4(void *self, void *obj, int a, int b);
extern int func_ov004_0221cf00(void *self, void *obj);
extern void func_ov004_0221cee4(void *self, int k);
extern void func_02015330(void *self, void *obj, int a, int b, int c);

void func_ov004_0221cd68(void *self)
{
    unsigned char b[4];
    char obj[8];
    int n;
    void *h;

    if (*(int *) ((char *) *(void **) ((char *) self + 0x1a4) + 0x898) == 0xb && func_0206fbc0() != 0) {
        if (func_0206fc6c() == 0) {
            *(int *) ((char *) *(void **) ((char *) self + 0x40) + 8) = 1;
            b[0] = (unsigned char) (func_020644cc(2) + 7);
            func_0206844c(*(void **) ((char *) self + 0x40), &b[0], 0);
            func_ov004_0221c844(*(void **) ((char *) self + 0x1a4), 6);
        } else {
            h = func_0206fc8c();
            *(short *) obj = (short) func_0209a034(h);
            n = func_0204c878(obj);
            func_0209a050(h);
            func_02015de4(self, obj, 0, 7);
            if (func_ov004_0221cf00(self, obj) != 0) {
                b[1] = (unsigned char) (func_020644cc(2) + 0xd);
                func_0206844c(*(void **) ((char *) self + 0x40), &b[1], 0);
                func_ov004_0221cee4(self, 5);
                if (n >= 0x3e8) {
                    func_ov004_0221cee4(self, 5);
                }
                if (n >= 0x7d0) {
                    func_ov004_0221cee4(self, 0xa);
                }
                func_02015330(self, obj, 0, 5, 0);
                func_ov004_0221c844(*(void **) ((char *) self + 0x1a4), 0xc);
            } else {
                b[2] = (unsigned char) (func_020644cc(2) + 0xb);
                func_0206844c(*(void **) ((char *) self + 0x40), &b[2], 0);
                func_ov004_0221cee4(self, 2);
                if (n >= 0x3e8) {
                    func_ov004_0221cee4(self, 5);
                }
                if (n >= 0x7d0) {
                    func_ov004_0221cee4(self, 5);
                }
                func_02015330(self, obj, 0, 5, 0);
                func_ov004_0221c844(*(void **) ((char *) self + 0x1a4), 0xc);
            }
        }
    }
}

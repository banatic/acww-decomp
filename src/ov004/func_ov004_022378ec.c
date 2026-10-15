/* func_ov004_022378ec @ 0x022378ec, 0x100 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
extern Vec *func_02095794(int);
extern int func_020e89dc(short *, int, int);
extern int func_020e88dc(int *, int, int);
extern int func_ov004_022377ec(void *);
extern void func_ov004_02237794(void *);
extern void func_ov004_02237834(void *);
extern int func_0200322c(Vec *, Vec *);
extern long long func_020ea940(Vec *, Vec *);
void func_ov004_022378ec(unsigned char *self)
{
    Vec *other = func_02095794(4);
    if (!other) {
        self[0x255] = 0;
    } else {
        long long distance;
        if (*(short *) (self + 0x1c4) != 0) {
            func_020e89dc((short *) (self + 0x1c4), 0, 0x16c);
        }
        if (*(int *) (self + 0x1ac) != 0x199a) {
            func_020e88dc((int *) (self + 0x1ac), 0x199a, *(int *) (self + 0x224));
        }
        switch (self[0x257]) {
            case 1:
                func_ov004_022377ec(self);
                break;
            case 2:
                func_ov004_02237794(self);
                break;
            case 0:
                func_ov004_02237834(self);
                break;
        }
        func_020e89dc((short *) (self + 0x1c0), func_0200322c((Vec *) (self + 0x1a8), other), 0x222);
        distance = func_020ea940(other, (Vec *) (self + 0x1a8));
        if (distance > 0x10000) {
            self[0x255] = 0;
            *(int *) (self + 0x158) = 0;
        } else if (distance > 0x4000) {
            self[0x255] = 1;
            *(int *) (self + 0x158) = 0;
        }
        *(int *) (self + 0x110) = 0x1000;
    }
}

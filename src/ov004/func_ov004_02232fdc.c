/* func_ov004_02232fdc @ 0x02232fdc, 0xa8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;

extern int func_02054ec4(void *);
extern void func_02055124(void *);
extern int func_ov004_022324b4(void *);
extern void func_02056ffc(void *);
extern int func_ov004_0223c1e0(void);
extern void func_020042a0(void *, int);
extern void func_020042c0(void *, Vec *);
extern void func_ov004_02232270(void *);
extern int data_021d3124;

int func_ov004_02232fdc(char *self)
{
    Vec v;
    char *p;
    if (func_02054ec4(self + 0x50) != 0) {
        func_02055124(self + 0x50);
    }
    p = self + 0x108;
    if (func_ov004_022324b4(p) != 0) {
        func_02056ffc(p);
        **(int **) (self + 0x120) = *(int *) (self + 0x110);
    }
    if (*(int *) (self + 0x3528) != 0) {
        int r = func_ov004_0223c1e0();
        if (r == 9 || r == 0x1d) {
            func_020042a0(self + 0x3534, 0x4d1);
        }
    }
    v = *(Vec *) (self + 0x3528);
    func_020042c0(self + 0x3534, &v);
    func_ov004_02232270(self + 0x34fc);
    data_021d3124 = 0;
    return 1;
}

/* func_ov004_0222ec34 @ 0x0222ec34, 0x12c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_020355e0(void);
extern int func_020e8b0c(int, int, int);
extern signed char *func_0200420c(void);
extern void func_02055124(void *);
extern void func_ov004_0222e65c(void *);
extern void func_02091278(int, void *, int, int);
extern int func_0209120c(int, void *, void *, int);
int func_ov004_0222ec34(unsigned char *self)
{
    unsigned char i;
    if (func_020e8b0c(func_020355e0(), 99, 171)) {
        signed char *record = func_0200420c();
        if (record && record[3] != 1) {
            *(int *) (self + 0x190) = 0;
            *(int *) (self + 0x198) = *(int *) (record + 16);
            func_02055124(self + 0xec);
            *(int *) (self + 0x198) = 0;
            *(int *) (self + 0x334) = 0;
            *(int *) (self + 0x33c) = *(int *) (record + 16);
            func_02055124(self + 0x290);
            *(int *) (self + 0x33c) = 0;
        }
    }
    func_02055124(self + 0xec);
    for (i = 0; i < 9; ++i) {
        func_02055124(self + 0x290 + i * 0xb8);
    }
    func_ov004_0222e65c(self);
    if (*(int *) (self + 0xf38) != -1) {
        func_02091278(*(int *) (self + 0xf38), self + 0xf10, 0, 0);
    }
    if (self[0xef4] && *(int *) (self + 0xf3c) == -1) {
        *(int *) (self + 0xf3c) = func_0209120c(107, self + 0xf1c, self + 0xf34, 0);
    }
    if (self[0xef6] && *(int *) (self + 0xf40) == -1) {
        *(int *) (self + 0xf40) = func_0209120c(107, self + 0xf28, self + 0xf36, 0);
    }
    return 1;
}

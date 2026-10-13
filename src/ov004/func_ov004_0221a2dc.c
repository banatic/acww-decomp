/* func_ov004_0221a2dc @ 0x0221a2dc, 0x144 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220ffbc(char *);
extern void func_ov004_0220d030(void *);
extern int func_ov004_0220d058(void *, int, int, int);
extern int func_ov004_0221081c(char *);
extern void func_ov004_0221a1d4(char *);
extern int func_ov004_0220fde0(char *);
extern int func_ov004_0220e5c8(char *);
extern void func_ov004_0223cf40(void *, int, void *);
extern int func_02056f28(void *, int);
extern void func_ov004_0223cf18(void *, int);
extern int func_ov004_022107d4(char *);
int func_ov004_0221a2dc(char *self)
{
    if (*(int *) (self + 0x780) == 1) {
        func_ov004_0220ffbc(self);
    }
    func_ov004_0220d030(self + 0x848);
    func_ov004_0220d058(self + 0x848, 1, 0, 0);
    func_ov004_0221081c(self);
    func_ov004_0221a1d4(self);
    switch (func_ov004_0220fde0(self)) {
        case 0x123:
            if (!func_ov004_0220e5c8(self)) {
                func_ov004_0223cf40(self + 0x798, 0x429, self + 0x7b8);
                if (func_02056f28(self + 0x5d4, 0x43)) {
                    func_ov004_0223cf18(self + 0x798, 1);
                }
            }
            break;
        case 0x1fb:
            if (!func_ov004_0220e5c8(self)) {
                func_ov004_0223cf40(self + 0x798, 0x42b, self + 0x7b8);
                if (func_02056f28(self + 0x5d4, 4)) {
                    func_ov004_0223cf18(self + 0x798, 1);
                } else if (func_02056f28(self + 0x5d4, 0x16)) {
                    func_ov004_0223cf18(self + 0x798, 2);
                }
            }
            break;
        case 0x1fc:
            if (!func_ov004_0220e5c8(self)) {
                func_ov004_0223cf40(self + 0x798, 0x42c, self + 0x7b8);
                if (func_02056f28(self + 0x5d4, 5) || func_02056f28(self + 0x5d4, 0x12)) {
                    func_ov004_0223cf18(self + 0x798, 1);
                }
            }
            break;
        default:
            func_ov004_022107d4(self);
            break;
    }
    return 1;
}

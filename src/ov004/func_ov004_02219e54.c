/* func_ov004_02219e54 @ 0x02219e54, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220fde0(void *self);
extern int func_ov004_0220d2a8(void *p);
extern void func_0205265c(void *self, int a, int b, int c);
extern void func_ov004_0220d290(void *p, int a);
extern int func_ov004_0220ffbc(void *self);
extern void func_ov004_022107d4(void *self);
extern int func_02056f28(void *p, int a);
extern void func_ov004_02210744(void *self);

void func_ov004_02219e54(char *self)
{
    int r = func_ov004_0220fde0(self);
    switch (r) {
        case 0xb9:
        case 0xba:
            if (func_ov004_0220d2a8(self + 0x740) != 0) {
                func_0205265c(self, 1, 0xff, 1);
                return;
            }
            break;
    }
    func_ov004_0220d290(self + 0x740, 0);
    if (func_ov004_0220ffbc(self) != 0) {
        func_0205265c(self, 0, 0xff, 1);
    } else {
        func_ov004_022107d4(self);
    }
    if (func_ov004_0220fde0(self) == 0x207) {
        if (func_02056f28(self + 0x5d4, 0x30) != 0) {
            func_ov004_02210744(self);
        }
    }
}

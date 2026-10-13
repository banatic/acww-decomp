/* func_ov004_02244c40 @ 0x02244c40, 0x118 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02244904(void *);
extern int func_ov004_02244c20(void *);
extern void func_020550e4(void *, int);
extern void func_02056fcc(void *, unsigned int, unsigned char, unsigned int, unsigned short);
extern int func_020644cc(int);
extern unsigned char data_ov004_02259a24;
void func_ov004_02244c40(unsigned char *self)
{
    unsigned char kind = self[0x196];
    func_ov004_02244904(self);
    if (!(func_ov004_02244c20(self) && self[0x22]) && !self[0x9a]) {
        if (kind == 10 || kind == 51) {
            if ((unsigned short) (*(unsigned int *) (self + 0x154) >> 12) != 0) {
                func_020550e4(self + 0xb0, 0);
            }
        } else if ((unsigned short) (*(unsigned int *) (self + 0x150) >> 12) < 12) {
            func_02056fcc(self + 0x14c, 17, 1, 0x1000, 9);
        } else if ((unsigned short) (*(unsigned int *) (self + 0x154) >> 12) == 16) {
            if ((self[0x22] || data_ov004_02259a24 % 10 == 0) && func_020644cc(100) > 95) {
                func_02056fcc(self + 0x14c, 17, 1, 0x1000, 9);
            }
        }
    } else {
        *(short *) (self + 0x172) = 25;
        *(int *) (self + 0x54) = *(int *) (self + 0xa8);
        *(int *) (self + 0x174) = (func_020644cc(10) + 16) * 20;
        if (kind != 10 && kind != 51) {
            func_02056fcc(self + 0x14c, 9, 0, *(unsigned int *) (self + 0x4c), 0);
        } else {
            func_020550e4(self + 0xb0, 1);
        }
    }
}

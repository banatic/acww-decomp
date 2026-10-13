/* func_ov004_022419f8 @ 0x022419f8, 0x164 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d088(void *);
extern void NNS_G3dMdlSetMdlAlpha(int, int, int);
extern int func_020644cc(int);
extern int func_ov004_0224193c(void *, short *);
extern int func_ov004_022419c4(void *);
extern void func_02056fcc(void *, unsigned int, unsigned char, unsigned int, unsigned short);
void func_ov004_022419f8(unsigned char *self)
{
    short *timer = (short *) (self + 0x98);
    switch (*(short *) (self + 0x172)) {
        case 2:
            if (self[0x170]) {
                self[0x170] = 0;
                *(short *) (self + 0x194) = 91;
            } else {
                self[0x170] = 1;
                *(short *) (self + 0x194) = -91;
            }
            if (((*(unsigned int *) (self + 0x154) << 4) >> 16) == 56) {
                *(short *) (self + 0x172) = 25;
                *(short *) (self + 0x194) = 0;
                *(int *) (self + 0x2c8) = *(int *) (self + 0x4c);
                NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x288), 0, 0);
                *(short *) (self + 0x98) = (func_020644cc(4) + 3) * 20;
            }
            break;
        case 1:
            if (((*(unsigned int *) (self + 0x154) << 4) >> 16) == 32) {
                *(short *) (self + 0x98) = (func_020644cc(3) + 2) * 20;
                *(short *) (self + 0x172) = 18;
                *(short *) (self + 0x168) = 0;
            }
            break;
        case 18:
            if (func_ov004_0224193c(self, (short *) (self + 0x168)) && *timer <= 0) {
                *(short *) (self + 0x192) = 0;
                *(short *) (self + 0x172) = 2;
                func_02056fcc(self + 0x14c, 57, 1, 0x1000, 32);
            } else {
                --*timer;
            }
            break;
        default:
            if (func_ov004_022419c4(self)) {
                if (*timer > 0) {
                    --*timer;
                } else {
                    *(short *) (self + 0x172) = 1;
                    *(short *) (self + 0x9c) = 0;
                    func_02056fcc(self + 0x14c, 33, 1, 0x1000, 0);
                    NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x288), 0, 31);
                }
            } else {
                self[0x160] = 1;
            }
            break;
    }
}

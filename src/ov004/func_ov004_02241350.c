/* func_ov004_02241350 @ 0x02241350, 0x158 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022411a4(void *, short *);
extern void func_ov004_02241084(void *);
extern int func_020644cc(int);
void func_ov004_02241350(unsigned char *self)
{
    short *timer = (short *) (self + 0x168);
    func_ov004_022411a4(self, timer);
    ++*(short *) (self + 0x168);
    if (*(short *) (self + 0x172) == 4) {
        func_ov004_02241084(self);
        if (*(signed char *) (self + 0x196) == 26) {
            if (*timer > 320 || (*timer % 20 == 0 && func_020644cc(100) > 90 && *timer > 160)) {
                *(short *) (self + 0x172) = 25;
                *timer = 0;
            }
        } else {
            if (*timer > 160 || (*timer % 20 == 0 && func_020644cc(100) > 90 && *timer > 80)) {
                *(short *) (self + 0x172) = 25;
                *timer = 0;
            }
        }
    } else if (*(signed char *) (self + 0x196) == 26) {
        if (self[0x22] && ((*(unsigned int *) (self + 0x154) << 4) >> 16) == 2) {
            if (*timer > 160 || (*timer % 20 == 0 && func_020644cc(100) > 85 && *timer >= 40)) {
                *timer = 0;
                *(short *) (self + 0x172) = 4;
            }
        }
    } else if (self[0x22]) {
        if (*timer > 80 || (*timer % 20 == 0 && func_020644cc(100) > 85)) {
            *(short *) (self + 0x172) = 4;
            *timer = 0;
        }
    } else {
        if (*timer > 800 || (*timer % 100 == 0 && func_020644cc(100) > 90)) {
            *(short *) (self + 0x172) = 4;
            *timer = 0;
        }
    }
}

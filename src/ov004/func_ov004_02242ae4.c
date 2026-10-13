/* func_ov004_02242ae4 @ 0x02242ae4, 0x180 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define W(p, o) (*(int *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
extern int func_ov004_02242820(void *), func_ov004_02242078(void *), func_ov004_02245188(void *),
    func_ov004_022447c0(int, int), func_020e8870(short *, int, int), func_ov004_02244c20(void *), func_020644cc(int),
    func_ov004_0224105c(int);
extern void func_02056fcc(void *, int, int, int, int), func_ov004_022425a8(void *), func_ov004_02242470(void *),
    func_ov004_02242334(void *), func_ov004_02242228(void *), func_ov004_022422fc(void *), func_ov004_02242180(void *);
void func_ov004_02242ae4(u8 *self)
{
    if (self[0x21]) {
        if (!func_ov004_02242820(self)) {
            return;
        }
    } else {
        if (func_ov004_02242078(self) == 1) {
            return;
        }
        if (*(signed char *) (self + 0x196) == 55) {
            unsigned frame = ((unsigned) W(self, 0x154) << 4) >> 16;
            if (frame > 3) {
                func_02056fcc(self + 0x14c, 3, 3, 0x1000, frame);
            } else if (frame == 3) {
                func_02056fcc(self + 0x14c, 3, 0, 0x1000, 0);
            }
        }
    }
    switch (S(self, 0x172)) {
        case 20:
            func_ov004_022425a8(self);
            break;
        case 21:
            func_ov004_02242470(self);
            break;
        case 22:
            func_ov004_02242334(self);
            break;
        case 23:
            func_ov004_02242228(self);
            break;
        case 24:
            func_ov004_022422fc(self);
            break;
        case 4:
            func_ov004_02242180(self);
            break;
        case 3:
        case 15: {
            int direction = func_ov004_02245188(self);
            if (direction && S(self, 0x172) == 3) {
                S(self, 0xac) = func_ov004_022447c0(S(self, 0x192), direction);
                S(self, 0x172) = 15;
            } else {
                short angle = S(self, 0x192);
                if (func_020e8870(&angle, S(self, 0xac), 0x71c)) {
                    S(self, 0x172) = 4;
                }
                S(self, 0x192) = angle;
            }
            break;
        }
        default:
            if (func_ov004_02244c20(self)) {
                short angle;
                int offset;
                self[0x9a] = 0;
                S(self, 0x172) = 3;
                W(self, 0x174) = (short) ((func_020644cc(3) + 1) * 20);
                angle = S(self, 0x192);
                offset = func_ov004_0224105c(16);
                offset += angle;
                S(self, 0xac) = offset;
            }
            break;
    }
}

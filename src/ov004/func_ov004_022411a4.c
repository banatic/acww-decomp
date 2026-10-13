/* func_ov004_022411a4 @ 0x022411a4, 0x1ac bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    Vec position;
    int value, distance;
    u8 present;
} Sample;
#define W(p, o) (*(int *) ((p) + (o)))
#define U(p, o) (*(unsigned *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
extern int func_ov004_02244658(void *, Sample *), func_0200322c(Vec *, Vec *);
extern void func_02056fcc(void *, unsigned, u8, unsigned, unsigned), func_020550e4(void *, int);
void func_ov004_022411a4(u8 *self, short *out)
{
    Sample sample;
    func_ov004_02244658(self, &sample);
    if (sample.present) {
        short amount = S(self, 0x9c);
        u8 *animation = self + 0xb0;
        signed char state;
        if (sample.distance <= 0xccd) {
            *out = 0;
            return;
        }
        state = *(signed char *) (self + 0x196);
        if ((u8) (signed char) (state - 14) <= 1) {
            if (self[0x50]) {
                S(self, 0x192) = func_0200322c((Vec *) (self + 0x2c8), &sample.position);
                S(self, 0x172) = 25;
            }
            if (amount > 20) {
                func_02056fcc(animation + 0x9c, 9, 1, 0x1000, (U(animation, 0xa4) << 4) >> 16);
                self[0x50] = 60;
            } else {
                u8 timer = self[0x50];
                if (timer) {
                    self[0x50] = timer - 1;
                } else if (sample.distance < W(self, 0xa0)) {
                    unsigned frame = (U(animation, 0xa4) << 4) >> 16;
                    if (frame == 0) {
                        func_02056fcc(animation + 0x9c, 4, 1, 0x1000, 0);
                        self[0x50] = 60;
                    } else if (frame > 4) {
                        func_02056fcc(animation + 0x9c, 4, 3, 0x1000, frame);
                    }
                } else {
                    unsigned frame = (U(animation, 0xa4) << 4) >> 16;
                    if (frame) {
                        func_02056fcc(animation + 0x9c, 0, 3, 0x1000, frame);
                    }
                }
            }
        } else if (state == 26) {
            if (amount > 20 || !self[0x22]) {
                unsigned frame = (U(animation, 0xa4) << 4) >> 16;
                if (frame == 2) {
                    func_020550e4(animation, 1);
                } else if (frame == 1) {
                    func_020550e4(animation, 0);
                    S(self, 0x172) = 25;
                    self[0x50] = 60;
                }
            } else {
                int frame = W(animation, 0xa4) >> 12;
                if ((u16) frame == 0 && !self[0x50]) {
                    func_020550e4(animation, 1);
                } else if ((u16) frame == 1) {
                    func_020550e4(animation, 2);
                } else {
                    u8 timer = self[0x50];
                    if (timer) {
                        self[0x50] = timer - 1;
                    }
                }
            }
        }
    }
}

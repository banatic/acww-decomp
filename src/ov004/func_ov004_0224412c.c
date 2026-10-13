/* func_ov004_0224412c @ 0x0224412c, 0xf8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
extern short func_ov004_0224105c(int);
extern int func_020644cc(int);
extern void func_ov004_02244f48(Vec *, Vec *, int, int);
extern int func_0200322c(Vec *, Vec *);
void func_ov004_0224412c(unsigned char *self)
{
    short *timer = (short *) (self + 0x168);
    Vec *position = (Vec *) (self + 0x2c8);
    if (*timer <= 0) {
        short mode = *(short *) (self + 0x172);
        if ((unsigned short) (short) (mode - 12) <= 1) {
            *(short *) (self + 0x172) = 15;
        } else if (mode == 14) {
            *(short *) (self + 0x172) = 19;
        } else {
            int angle;
            if (*(signed char *) (self + 0x196) == 23) {
                // Snapshot before the random call, as the ROM does.
                int previous = *(short *) (self + 0x192);
                int delta = func_ov004_0224105c(4);
                *(short *) (self + 0xac) = delta + previous;
            } else {
                // Snapshot before the random call, as the ROM does.
                int previous = *(short *) (self + 0x192);
                int delta = func_ov004_0224105c(12);
                *(short *) (self + 0xac) = delta + previous;
            }
            *(short *) (self + 0x172) = 3;
            angle = *(short *) (self + 0xac);
            func_ov004_02244f48((Vec *) (self + 0x34), position, angle, (self[0xa4] + func_020644cc(3)) << 12);
            *(short *) (self + 0xac) = func_0200322c((Vec *) (self + 0x2c8), (Vec *) (self + 0x34));
        }
    } else {
        if (*timer % 10 < 5) {
            if (position->y < *(int *) (self + 0xa8) + 0x800) {
                position->y += 0x80;
            }
        } else {
            if (position->y > *(int *) (self + 0xa8) - 0x1000) {
                position->y -= 0x80;
            }
        }
        --*timer;
    }
}

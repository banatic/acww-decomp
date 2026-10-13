/* func_ov004_022449ec @ 0x022449ec, 0xf8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
extern int func_020644cc(int);
extern void func_ov004_02244fb8(Vec *, int);
extern int FX_MulFunc(int, int);
extern unsigned char data_ov004_02259a24;
void func_ov004_022449ec(unsigned char *self, int step, int period, unsigned int threshold)
{
    short angle = *(short *) (self + 0x192);
    unsigned char direction = self[0xae];
    unsigned char random = (unsigned char) func_020644cc(100);
    Vec *position = (Vec *) (self + 0x2c8);
    Vec offset;
    if (data_ov004_02259a24 % period == 0 && random > threshold) {
        if (!direction) {
            direction = 1;
        } else {
            direction = 0;
        }
        self[0xae] = direction;
    }
    if (random > self[0x50]) {
        if (direction) {
            angle += step;
        } else {
            angle -= step;
        }
    }
    func_ov004_02244fb8(&offset, angle);
    *(short *) (self + 0x192) = angle;
    if (self[0x9a]) {
        position->x += FX_MulFunc(FX_MulFunc(0x1800, *(int *) (self + 0x16c) << 12), offset.x);
        position->z += FX_MulFunc(FX_MulFunc(0x1800, *(int *) (self + 0x16c) << 12), offset.z);
    } else {
        position->x += FX_MulFunc(*(int *) (self + 0x16c) << 12, offset.x);
        position->z += FX_MulFunc(*(int *) (self + 0x16c) << 12, offset.z);
    }
}

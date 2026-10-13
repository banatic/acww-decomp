/* func_ov004_02242f1c @ 0x02242f1c, 0xcc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
extern int func_ov004_02242fe8(void *);
extern int func_ov004_02244c20(void *);
extern int func_020e908c(Vec *, Vec *, int, int, int);
extern void func_ov004_02242e84(void *);
extern int func_0200322c(Vec *, Vec *);
extern int func_020644cc(int);
void func_ov004_02242f1c(unsigned char *self)
{
    if (func_ov004_02242fe8(self)) {
        Vec *position = (Vec *) (self + 0x2c8);
        Vec *target = (Vec *) (self + 0x34);
        if (!func_ov004_02244c20(self)) {
            if (!func_020e908c(position, target, 64, 0x1000, 41)) {
                func_ov004_02242e84(self);
                *(short *) (self + 0xac) = func_0200322c(position, target);
                *(short *) (self + 0x172) = 3;
            } else {
                short timer = (short) *(int *) (self + 0x174);
                *(short *) (self + 0x192) = func_0200322c(position, target);
                if (timer % 8 == 0) {
                    *(short *) (self + 0x192) += 0xaaa;
                } else if (timer % 4 == 0) {
                    *(short *) (self + 0x192) -= 0xaaa;
                }
            }
        } else {
            *(int *) (self + 0x174) = (func_020644cc(3) + 2) * 20;
            *(short *) (self + 0x172) = 25;
        }
    }
}

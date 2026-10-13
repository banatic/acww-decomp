/* func_ov004_02243484 @ 0x02243484, 0xc0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
extern int func_020e908c(Vec *, Vec *, int, int, int);
extern int FX_MulFunc(int, int);
extern unsigned char *func_020961a8(int);
extern int func_020ea990(Vec *, Vec *);
extern int func_020644cc(int);
extern int func_ov004_02244e94(Vec *, Vec *);
void func_ov004_02243484(unsigned char *self)
{
    short *timer = (short *) (self + 0x98);
    Vec *position = (Vec *) (self + 0x2c8);
    Vec previous;
    previous.x = position->x;
    previous.y = position->y;
    previous.z = position->z;
    func_020e908c(position, (Vec *) (self + 0x34), 0xaa, 0x1000, 0x333);
    if (*(short *) (self + 0x98) > 0) {
        int t = *(short *) (self + 0x98) << 12;
        position->y = FX_MulFunc(0x99a - FX_MulFunc(123, t), t);
        if (position->y < 0) {
            unsigned char *other = func_020961a8(4);
            int spread = 20;
            if (other && func_020ea990((Vec *) (other + 0x5c), position) > 0x6000) {
                spread = 0;
            }
            *(int *) (self + 0x174) = (short) (func_020644cc(spread * 2 + 20) + 20) >> 1;
            *(short *) (self + 0x172) = 25;
            *timer = 0;
        } else {
            ++*timer;
        }
    }
    func_ov004_02244e94(position, &previous);
}

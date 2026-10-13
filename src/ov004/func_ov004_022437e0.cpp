/* func_ov004_022437e0 @ 0x022437e0, 0x168 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
extern "C" char *func_020961a8(int);
extern "C" int func_020ea990(Vec *, Vec *);
extern "C" short func_0200322c(Vec *, Vec *);
extern "C" int func_020e8870(short *, int, short);
extern "C" int func_020959ac(void);
extern "C" int func_020644cc(int);
extern "C" void func_ov004_02244fb8(Vec *, int);
extern "C" int FX_MulFunc(int, int);
extern "C" void func_ov004_0224497c(void *, int, int, int);
extern "C" void func_ov004_022437e0(unsigned char *self, short *phase)
{
    char *actor = func_020961a8(4);
    if (actor) {
        Vec *position = (Vec *) (self + 0x2c8);
        Vec *target = (Vec *) actor;
        short angle;
        Vec unit;
        target = (Vec *) ((char *) target + 0x5c);
        int distance = func_020ea990(target, position);
        angle = *(short *) (self + 0x192);
        func_020e8870(&angle, func_0200322c(position, target), 0x38e);
        *phase += 0xaaa;
        if (self[0x9a]) {
            short timer = *(short *) (self + 0x9c);
            if (distance > 0x3000) {
                self[0x9a] = 0;
            } else if (timer < 60) {
                ++timer;
                *(short *) (self + 0x9c) = (unsigned char) timer;
            } else if (*(int *) (self + 0x4c) == 0 && distance < 0x1000 && func_020959ac()) {
                self[0x9a] = 0;
                *(short *) (self + 0x172) = 0;
                *(int *) (self + 0x4c) = 1;
                *phase = 0;
            }
        }
        if (distance < 0x2000) {
            if (distance < 0x1000 && !self[0x9a]) {
                self[0x9a] = 1;
                *(short *) (self + 0x9c) = 0;
            }
            if (func_020644cc(100) > 30) {
                if (angle > 0) {
                    angle += 0x5b0;
                } else if (angle < 0) {
                    angle -= 0x5b0;
                }
            }
        }
        *(short *) (self + 0x192) = angle;
        func_ov004_02244fb8(&unit, angle);
        position->x += FX_MulFunc(unit.x, 0x8000);
        position->z += FX_MulFunc(unit.z, 0x8000);
        func_ov004_0224497c(self, *phase, 0x2800, (func_020644cc(4) + 18) << 12);
    }
}

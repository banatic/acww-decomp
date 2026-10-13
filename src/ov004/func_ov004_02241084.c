/* func_ov004_02241084 @ 0x02241084, 0x120 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
extern int func_020644cc(int);
extern unsigned char data_ov004_02259a24;
extern void func_ov004_02244fb8(Vec *, int);
extern int FX_MulFunc(int, int);
void func_ov004_02241084(unsigned char *self)
{
    int *upper = (int *) self;
    int *lower;
    short angle;
    int direction;
    Vec *position;
    // The escaping unit and saved position share this ROM-ordered frame.
    struct {
        Vec unit, old;
    } frame;
    upper = (int *) ((unsigned char *) upper + 0x60);
    lower = (int *) self;
    lower = (int *) ((unsigned char *) lower + 0x58);
    angle = *(short *) (self + 0x192);
    direction = self[0xae];
    position = (Vec *) (self + 0x2c8);
    frame.old.x = position->x;
    frame.old.y = position->y;
    frame.old.z = position->z;
    if (func_020644cc(100) > 80) {
        if ((int) data_ov004_02259a24 % 20 == 0) {
            direction = !direction;
            self[0xae] = direction;
        }
        if (direction) {
            angle += (short) *(int *) (self + 0x4c);
        } else {
            angle -= (short) *(int *) (self + 0x4c);
        }
    }
    func_ov004_02244fb8(&frame.unit, angle);
    *(short *) (self + 0x192) = angle;
    position->z += FX_MulFunc(FX_MulFunc(*(int *) (self + 0x16c) << 12, frame.unit.z), 128);
    position->x += FX_MulFunc(FX_MulFunc(*(int *) (self + 0x16c) << 12, frame.unit.x), 128);
    if (position->x < lower[0] || position->x > upper[0]) {
        position->x = frame.old.x;
    }
    if (position->z < lower[1] || position->z > upper[1]) {
        position->z = frame.old.z;
    }
    {
        int previous = frame.old.z;
        if (position->z != previous) {
            position->y -= position->z - previous;
        }
    }
    // Preserve the contradictory condition present in the ROM.
    if (position->y < 0x900 && position->y > 0x1000) {
        position->y = frame.old.y;
    }
}

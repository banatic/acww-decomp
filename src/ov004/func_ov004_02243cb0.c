/* func_ov004_02243cb0 @ 0x02243cb0, 0x154 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
extern int func_ov004_02245188(void *);
extern int func_020e908c(Vec *, Vec *, int, int, int);
extern int func_ov004_02244e38(void *, Vec *);
extern short func_0200322c(Vec *, Vec *);
extern int func_020e8bb0(int *, int, int, int, int);
extern int func_02034270(void *, Vec *, int, int);
extern int func_020341c8(void *, int);
extern void *func_0203423c(void *);
extern int func_020644cc(int);
extern void func_020550e4(void *, int);
void func_ov004_02243cb0(unsigned char *self)
{
    Vec *origin, *position;
    int speed;
    // One frame preserves the ROM height/old-position offsets around the ground query.
    struct {
        int height;
        Vec old;
        int ground[16];
    } frame;
    origin = (Vec *) (self + 0x34);
    position = (Vec *) (self + 0x2c8);
    frame.old.x = position->x;
    frame.old.y = position->y;
    frame.old.z = position->z;
    speed = *(int *) (self + 0x16c);
    if (!func_ov004_02245188(self) || self[0x20]) {
        if (func_020e908c(position, origin, speed, 0x1000, 0x333)) {
            if (func_ov004_02244e38(self, position)) {
                position->x = frame.old.x;
                position->y = frame.old.y;
                position->z = frame.old.z;
                origin->x = position->x;
                origin->y = position->y;
                origin->z = position->z;
            } else {
                *(short *) (self + 0x192) = func_0200322c(position, origin);
            }
        }
    } else {
        origin->x = position->x;
        origin->y = position->y;
        origin->z = position->z;
    }
    if (self[0x170]) {
        if (!func_020e8bb0(&position->y, 0x1400, speed, 0x1000, 0xcd)) {
            self[0x170] = 0;
        }
    } else {
        func_02034270(frame.ground, position, 0, 1);
        frame.height = func_020341c8(frame.ground, 0);
        func_0203423c(frame.ground);
        if (!func_020e8bb0(&position->y, frame.height, speed, 0x1000, 0x266)) {
            *(short *) (self + 0x98) = (func_020644cc(9) + 2) * 20;
            *(short *) (self + 0x172) = 25;
            func_020550e4(self + 0xb0, 0);
            origin->x = position->x;
            origin->y = position->y;
            origin->z = position->z;
            if (self[0x9a]) {
                *(short *) (self + 0x9c) = (unsigned char) (*(short *) (self + 0x9e) - 10);
                self[0x9a] = 0;
            }
        }
    }
}

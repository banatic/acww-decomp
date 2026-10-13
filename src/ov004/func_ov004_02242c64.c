/* func_ov004_02242c64 @ 0x02242c64, 0x120 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
extern int func_020644cc(int);
extern unsigned char data_ov004_02259a24;
void func_ov004_02242c64(unsigned char *self)
{
    unsigned char horizontal = self[0xae];
    Vec *position = (Vec *) (self + 0x2c8);
    int *origin = (int *) self;
    unsigned char vertical;
    // The ROM retains all three snapshot stores, including unused Z.
    volatile Vec old;
    int clock, distance;
    origin = (int *) ((unsigned char *) origin + 0x40);
    vertical = self[0x170];
    old.x = position->x;
    old.y = position->y;
    old.z = position->z;
    if (func_020644cc(100) > 30) {
        clock = data_ov004_02259a24;
        if (clock % 10 == 0) {
            self[0x170] = !vertical;
        } else if (clock % 5 == 0) {
            self[0xae] = !horizontal;
        }
    }
    if (horizontal) {
        position->x += 48 * *(int *) (self + 0x16c);
    } else {
        position->x -= 48 * *(int *) (self + 0x16c);
    }
    if (vertical) {
        position->y += 48 * *(int *) (self + 0x16c);
    } else {
        position->y -= 48 * *(int *) (self + 0x16c);
    }
    distance = position->x - origin[0];
    if (distance < 0) {
        distance = -distance;
    }
    if (distance > 0x1000) {
        self[0xae] = !horizontal;
        position->x = old.x;
    }
    distance = position->y - origin[1];
    if (distance < 0) {
        distance = -distance;
    }
    if (distance > 0x800) {
        self[0x170] = !vertical;
        position->y = old.y;
    }
}

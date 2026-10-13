/* func_ov004_0221e8f0 @ 0x0221e8f0, 0x150 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern int func_02019de8(void *);
extern int func_02019e00(void *);
extern int func_020644cc(int);
extern int func_ov004_0221ea98(void *, int *, int *, void *);
extern int func_02019d0c(void *, int, int, int, int, short, short, int, int, unsigned short, unsigned short);
int func_ov004_0221e8f0(char *self, char *actor)
{
    void *queue = actor + 0x564;
    int x, y;
    short angle;
    if (func_02019de8(queue)) {
        x = 0;
        y = 0;
        if (func_020644cc(7) == 0) {
            if (*(short *) (actor + 0x8e) & 0x3fff) {
                angle = func_020644cc(4) << 14;
                if (angle == *(short *) (actor + 0x8e)) {
                    angle += 0x4000;
                }
                func_02019d0c(queue, 3, 1, 0, 0, 0, angle, 0, 0, data_020c80f8, 0);
            } else if (func_020644cc(3) != 0 && func_ov004_0221ea98(self, &x, &y, actor)) {
                func_02019d0c(queue, 1, 1, x, y, 0, 0, 0, 0, data_020c80f8, 0);
                *(int *) (self + 0x10) = 60;
            } else {
                angle = func_020644cc(4) << 14;
                if (angle == *(short *) (actor + 0x8e)) {
                    angle += 0x4000;
                }
                func_02019d0c(queue, 3, 1, 0, 0, 0, angle, 0, 0, data_020c80f8, 0);
            }
        } else {
            func_02019d0c(queue, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
    } else if (*(int *) (self + 0x10) == 0 && func_02019e00(queue) == 1) {
        func_02019d0c(queue, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    }
    return 0;
}

/* func_ov004_02242470 @ 0x02242470, 0x138 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
extern unsigned char data_ov004_02259a24;
extern short FX_SinCosTable_[];
extern char *func_ov004_0223ee38(void);
extern short func_0200322c(Vec *, Vec *);
extern int func_020644cc(int);
extern int func_020ea990(Vec *, Vec *);
extern int FX_MulFunc(int, int);
extern void func_ov004_02242a9c(char *, int, int);
extern int func_ov004_02244c20(char *);
void func_ov004_02242470(char *self)
{
    char *other;
    Vec *own, *target, *origin;
    short angle;
    short *timer;
    int offset, index, distance;
    other = func_ov004_0223ee38();
    own = (Vec *) (self + 0x2c8);
    target = (Vec *) (other + 0x2c8);
    origin = (Vec *) other;
    origin = (Vec *) ((char *) origin + 0x34);
    angle = func_0200322c(own, target);
    timer = (short *) (self + 0x168);
    offset = *(int *) (self + 0x4c);
    if ((int) data_ov004_02259a24 % 10 == 0) {
        if (func_020644cc(100) > 50) {
            self[0x170] = 1;
        } else {
            self[0x170] = 0;
        }
    }
    if (*(unsigned char *) (self + 0x170) && offset < 0x1554) {
        angle += 0xb6;
        offset += 0xb6;
    } else if (!*(unsigned char *) (self + 0x170) && offset > 0) {
        angle -= 0xb6;
        offset -= 0xb6;
    } else if (*(unsigned char *) (self + 0x170)) {
        self[0x170] = 0;
    } else {
        self[0x170] = 1;
    }
    distance = func_020ea990(origin, own);
    index = ((unsigned short) angle >> 4) * 2;
    target->x = own->x + FX_MulFunc(FX_SinCosTable_[index], distance);
    target->z = own->z + FX_MulFunc(FX_SinCosTable_[index + 1], distance);
    *(short *) (self + 0x192) = angle;
    angle = func_0200322c(target, own);
    *(short *) (other + 0x192) = angle;
    func_ov004_02242a9c(other, angle, *timer);
    *(int *) (self + 0x4c) = offset;
    ++*timer;
    if (func_ov004_02244c20(self)) {
        *(short *) (self + 0x172) = 25;
        *timer = 0;
    }
}

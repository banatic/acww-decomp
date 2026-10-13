/* func_ov004_0223d9c4 @ 0x0223d9c4, 0x144 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
extern "C" short FX_SinCosTable_[];
static inline int table_index(short angle)
{
    return ((unsigned short) angle >> 4) * 2;
}
extern "C" void func_ov004_0223d9c4(char *self, int distance, int spread)
{
    Vec *position;
    short angle;
    int index;
    position = (Vec *) (self + 0x5c);
    angle = *(short *) (self + 0x8e);
    *(int *) (self + 0x230) = position->x;
    *(int *) (self + 0x234) = position->y;
    *(int *) (self + 0x238) = position->z;
    *(int *) (self + 0x23c) = position->x;
    *(int *) (self + 0x240) = position->y;
    *(int *) (self + 0x244) = position->z;
    *(int *) (self + 0x248) = *(int *) (self + 0x230);
    *(int *) (self + 0x24c) = *(int *) (self + 0x234);
    *(int *) (self + 0x250) = *(int *) (self + 0x238);
    *(int *) (self + 0x254) = *(int *) (self + 0x23c);
    *(int *) (self + 0x258) = *(int *) (self + 0x240);
    *(int *) (self + 0x25c) = *(int *) (self + 0x244);
    index = table_index(angle + spread);
    *(int *) (self + 0x230) += distance * FX_SinCosTable_[index] / 100;
    *(int *) (self + 0x238) += distance * FX_SinCosTable_[index + 1] / 100;
    *(int *) (self + 0x234) = 0x200;
    index = table_index(angle - spread);
    *(int *) (self + 0x23c) += distance * FX_SinCosTable_[index] / 100;
    *(int *) (self + 0x244) += distance * FX_SinCosTable_[index + 1] / 100;
    *(int *) (self + 0x240) = 0x200;
}

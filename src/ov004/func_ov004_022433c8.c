/* func_ov004_022433c8 @ 0x022433c8, 0xbc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
extern int func_ov004_02244be0(void *, int);
extern void func_ov004_02243194(void *, short *);
extern void func_ov004_02243248(void *, short *);
extern int func_020e8870(short *, int, int);
extern int func_ov004_02244c20(void *);
extern void func_ov004_02243300(void *);
void func_ov004_022433c8(unsigned char *self)
{
    switch (*(short *) (self + 0x172)) {
        case 4:
            func_ov004_02244be0(self, 2);
            func_ov004_02243194(self, (short *) (self + 0x168));
            break;
        case 5:
            func_ov004_02243248(self, (short *) (self + 0x168));
            break;
        case 3: {
            short angle = *(short *) (self + 0x192);
            if (func_020e8870(&angle, *(short *) (self + 0xac), 0x38e)) {
                *(short *) (self + 0x172) = 4;
            }
            func_ov004_02244be0(self, 2);
            *(short *) (self + 0x192) = angle;
            break;
        }
        case 16:
            if (func_ov004_02244c20(self)) {
                Vec *source, *destination;
                *(short *) (self + 0x172) = 25;
                source = (Vec *) (self + 0x34);
                destination = (Vec *) (self + 0x2c8);
                destination->x = source->x;
                destination->y = source->y;
                destination->z = source->z;
            }
            break;
        default:
            func_ov004_02243300(self);
            break;
    }
}

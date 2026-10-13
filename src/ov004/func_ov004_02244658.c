/* func_ov004_02244658 @ 0x02244658, 0x10c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    Vec position;
    int value;
    int distance;
    unsigned char present;
} Sample;
extern unsigned char *func_020961a8(int);
extern int func_020ea990(Vec *, Vec *);
int func_ov004_02244658(unsigned char *self, Sample *sample)
{
    short amount = *(short *) (self + 0x9c);
    short before = amount;
    short threshold = *(short *) (self + 0x9e);
    unsigned char *other = func_020961a8(4);
    if (other) {
        Vec *p;
        sample->present = 1;
        sample->value = *(int *) (other + 0x98);
        p = (Vec *) (other + 0x5c);
        sample->position.x = p->x;
        sample->position.y = p->y;
        sample->position.z = p->z;
        sample->distance = func_020ea990((Vec *) (self + 0x2c8), &sample->position);
        if (sample->distance < 0x2000) {
            amount += 25;
        } else if (sample->distance > *(int *) (self + 0xa0) || sample->value == 0) {
            --amount;
        } else if (sample->value <= 1000) {
            ++amount;
        } else if (sample->value <= 1100) {
            amount += 3;
        } else if (sample->value <= 1168) {
            amount += 5;
        } else if (sample->value == 1169) {
            amount += 8;
        } else {
            amount += 15;
        }
        if (amount < 0) {
            amount = 0;
        } else if (amount > 255) {
            amount = 255;
        }
        *(short *) (self + 0x9c) = (unsigned char) amount;
        if (threshold <= amount) {
            if (threshold > before) {
                return 1;
            }
            return 3;
        } else if (threshold > amount && threshold <= before) {
            return 2;
        }
    } else {
        sample->present = 0;
        return -1;
    }
    return 0;
}

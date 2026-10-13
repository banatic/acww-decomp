/* func_ov004_02235b28 @ 0x02235b28, 0x12c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
extern unsigned char *data_ov004_022594d4[];
extern void func_ov004_022359c8(void *, void *);
extern int func_0200322c(Vec *, Vec *);
void func_ov004_02235b28(unsigned char *self)
{
    int own;
    unsigned char **slot;
    Vec *position;
    unsigned char *other;
    int angle;
    int theirs;
    slot = &data_ov004_022594d4[self[0x1e8]];
    other = *slot;
    if (other) {
        position = (Vec *) (other + 0x1a8);
        own = *(short *) (self + 0x1c0);
        if (own < 0) {
            own = -own;
        }
        angle = *(short *) (other + 0x1c0);
        theirs = angle < 0 ? -angle : angle;
        if (own >= 0x4000 && theirs >= 0x4000) {
            if (*(int *) (self + 0x1b0) > position->z) {
                *(short *) (self + 0x1ec) = angle + 0x8000;
            } else if (!other[0x1c9]) {
                other[0x1c9] = 1;
                (*slot)[0x1e9] = *(int *) (self + 0x15c);
                *(short *) (*slot + 0x1ec) = *(short *) (self + 0x1c0) + 0x8000;
            }
            func_ov004_022359c8(self, slot);
        } else if (own <= 0x4000 && theirs <= 0x4000) {
            if (*(int *) (self + 0x1b0) < position->z) {
                *(short *) (self + 0x1ec) = angle + 0x8000;
            } else if (!other[0x1c9]) {
                other[0x1c9] = 1;
                (*slot)[0x1e9] = *(int *) (self + 0x15c);
                *(short *) (*slot + 0x1ec) = *(short *) (self + 0x1c0) + 0x8000;
            }
            func_ov004_022359c8(self, slot);
        } else {
            int target = func_0200322c(position, (Vec *) (self + 0x1a8));
            if ((short) (target - *(short *) (self + 0x1c0)) < 0) {
                *(short *) (self + 0x1ec) = target - 0x4000;
            } else {
                *(short *) (self + 0x1ec) = target + 0x4000;
            }
        }
    }
}

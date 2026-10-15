/* func_ov004_02243300 @ 0x02243300, 0xc8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    Vec position;
    int value, distance;
    unsigned char present;
} Sample;
extern int func_ov004_02244658(void *, Sample *);
extern int func_ov004_02244be0(void *, int);
extern int func_02090c2c(int, Vec *, int, void *);
extern int func_020644cc(int);
extern int func_0200322c(Vec *, Vec *);
extern void *func_0209d088(void *);
extern void NNS_G3dMdlSetMdlAlpha(void *, int, int);
extern unsigned char data_020e25d4[];
void func_ov004_02243300(unsigned char *self)
{
    // Declaration order recovers r4/r6/r7 without altering evaluation order.
    unsigned char before;
    Sample sample;
    int countdown;
    Vec *position;
    position = (Vec *) (self + 0x2c8);
    before = (unsigned char) *(short *) (self + 0x9c);
    func_ov004_02244658(self, &sample);
    if (sample.present) {

        if (sample.distance < 0x5000) {
            self[0x50] = 60;
        }
        countdown = self[0x50];
        if (countdown > 0) {
            func_ov004_02244be0(self, 0);
            self[0x50] = countdown - 1;
        }
        if (before > *(short *) (self + 0x9e)) {
            Vec *destination;
            Vec *source;
            *(short *) (self + 0x172) = 5;
            func_02090c2c(128, position, 0, data_020e25d4);
            *(short *) (self + 0x98) = (func_020644cc(11) + 5) * 20;
            *(short *) (self + 0x192) = func_0200322c(&sample.position, position);
            NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x288), 0, 31);
            source = (Vec *) (self + 0x2c8);
            destination = (Vec *) (self + 0x34);
            destination->x = source->x;
            destination->y = source->y;
            destination->z = source->z;
        }
    }
}

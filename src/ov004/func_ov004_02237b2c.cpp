/* func_ov004_02237b2c @ 0x02237b2c, 0xe8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct Actor {};
typedef void (Actor::*Action)();
struct Vec {
    int x, y, z;
};
extern "C" {
extern Action data_ov004_0225949c[];
extern void func_ov004_02239b80(void *);
extern void func_ov004_02239768(void *);
extern void func_ov004_022395d0(void *, int, int);
extern void func_ov004_0223592c(void *);
extern void func_ov004_022358c0(void *, int);
extern unsigned char *func_020961a8(int);
extern long long func_020ea940(Vec *, Vec *);
}
extern "C" void func_ov004_02237b2c(unsigned char *self)
{
    (((Actor *) self)->*data_ov004_0225949c[self[0x1ee]])();
    func_ov004_02239b80(self);
    if (self[0x1ee] != 2 && self[0x1ee] != 6) {
        func_ov004_02239768(self);
        func_ov004_022395d0(self, 0x1554, 0x384);
        func_ov004_0223592c(self);
    }
    func_ov004_022358c0(self, 0x666);
    unsigned char *other = func_020961a8(4);
    if (other) {
        Vec position;
        Vec *source = (Vec *) (other + 0x5c);
        position.x = source->x;
        position.y = source->y;
        position.z = source->z;
        if (func_020ea940(&position, (Vec *) (self + 0x1a8)) < 0x10000) {
            ++self[0x259];
            if (self[0x259] > 10 && *(int *) (other + 0x98) != 0) {
                self[0x255] = 1;
                *(int *) (self + 0x158) = 0;
                self[0x259] = 0;
            }
        } else {
            self[0x259] = 0;
        }
    }
}

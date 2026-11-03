/* aquarium_fish_kinds_5: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02237c14 @ 0x02237c14, 0xf0 bytes, Thumb
 * func_ov004_02237b2c @ 0x02237b2c, 0xe8 bytes, Thumb
 */

struct Actor {};

typedef void (Actor::*Action)();

struct Vec {
    int x, y, z;
};

extern "C" {
extern Action data_ov004_022593f4[];
extern unsigned char data_ov004_02247b24[];
extern unsigned char data_ov004_022593c4[];
extern int func_02031168(Vec *, int, void *, int, int);
extern void func_02089bec(void *, Vec *, int, int, int, int, int, unsigned char, int);
extern void func_02089fc8(void *);
}

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

extern "C" void func_ov004_02237c14(unsigned char *self)
{
    (((Actor *) self)->*data_ov004_022593f4[self[0x255]])();
    int size = (data_ov004_02247b24[1] << 12) >> 7;
    self[0x256] = func_02031168((Vec *) (self + 0x1a8), size, data_ov004_022593c4, 0x11c00, 0x5c00);
    func_02089bec(self + 4, (Vec *) (self + 0x1a8), size, (data_ov004_02247b24[0] << 12) >> 7, 0x100, 0x140, 0, 255,
                  (self[0x164] << 12) / 10);
    func_02089fc8(self + 4);
    *(int *) (self + 0x1b4) = *(int *) (self + 0x1a8);
    *(int *) (self + 0x1b8) = *(int *) (self + 0x1ac);
    *(int *) (self + 0x1bc) = *(int *) (self + 0x1b0);
    ++*(int *) (self + 0x158);
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

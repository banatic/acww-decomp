/* func_ov004_02237c14 @ 0x02237c14, 0xf0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct Actor {};
typedef void (Actor::*Action)();
struct Vec {
    int x, y, z;
};
extern "C" {
extern Action data_ov004_022593f4[];
extern unsigned char data_ov004_02247b24[], data_ov004_022593c4[];
extern int func_02031168(Vec *, int, void *, int, int);
extern void func_02089bec(void *, Vec *, int, int, int, int, int, unsigned char, int);
extern void func_02089fc8(void *);
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

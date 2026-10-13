/* func_ov004_02238a58 @ 0x02238a58, 0x14c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class Actor;
typedef void (Actor::*Method)();
extern "C" Method data_ov004_0225946c[];
extern "C" unsigned char data_ov004_02247928[];
extern "C" int func_020e89dc(short *, int, short);
extern "C" int func_ov004_02239bb4(void *, int, int);
extern "C" void func_ov004_022398a8(void *, int);
extern "C" void func_ov004_022355f4(void *);
extern "C" void func_ov004_02235c54(void *);
extern "C" void func_ov004_0223592c(void *);
extern "C" void func_ov004_02235e58(void *);
extern "C" int func_ov004_02239858(void *);
extern "C" void func_ov004_022358c0(void *, int);
static inline int height(int id)
{
    return data_ov004_02247928[17 * id] << 12;
}
extern "C" void func_ov004_02238a58(unsigned char *self, int left, int right)
{
    if (*(int *) (self + 0x1a8) <= ((left + 2) << 12)) {
        self[0x1fc] = 1;
        if (func_020e89dc((short *) (self + 0x1c0), 0x4000, 0x38e)) {
            *(int *) (self + 0x1a8) += 0x19a;
        }
        *(int *) (self + 0x1ac) = height(*(int *) (self + 0x15c)) >> 6;
        func_ov004_02239bb4(self + 0x1a8, 0x19a, *(short *) (self + 0x1c0));
        *(int *) (self + 0x110) = 0x1000;
        func_ov004_022398a8(self, 3);
    } else if (*(int *) (self + 0x1a8) >= ((right - 2) << 12)) {
        self[0x1fc] = 1;
        if (func_020e89dc((short *) (self + 0x1c0), -0x4000, 0x38e)) {
            *(int *) (self + 0x1a8) -= 0x19a;
        }
        *(int *) (self + 0x1ac) = height(*(int *) (self + 0x15c)) >> 6;
        func_ov004_02239bb4(self + 0x1a8, 0x19a, *(short *) (self + 0x1c0));
        *(int *) (self + 0x110) = 0x1000;
        func_ov004_022398a8(self, 10);
    } else {
        func_ov004_022355f4(self);
        func_ov004_02235c54(self);
        (((Actor *) self)->*data_ov004_0225946c[self[0x1ee]])();
        func_ov004_0223592c(self);
        func_ov004_02235e58(self);
        func_ov004_02239858(self);
        func_ov004_022358c0(self, 0x333);
    }
}

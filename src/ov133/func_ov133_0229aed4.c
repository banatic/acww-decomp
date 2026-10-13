/* func_ov133_0229aed4 @ 0x0229aed4, 0xbc bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov133_0229ad88(void *self, int size);
extern void func_ov133_0229afec(void *self);
extern void func_ov133_0229af90(void *self);
extern void func_ov133_0229ad68(void *self, int size);
extern void func_ov133_0229ad78(void *self, int size);
extern int func_020b9bbc(void *dst, void *src, int count, int size, int flag);

void func_ov133_0229aed4(void *self)
{
    if (func_ov133_0229ad88(self, 8)) {
        func_ov133_0229afec(self);
        func_ov133_0229ad68(self, 8);
        func_ov133_0229ad78(self, 4);
    }
    if (func_ov133_0229ad88(self, 16)) {
        func_ov133_0229af90(self);
        func_ov133_0229ad68(self, 16);
        func_ov133_0229ad78(self, 4);
    }
    if (func_ov133_0229ad88(self, 2)) {
        if (func_020b9bbc((void *) ((char *) self + 0x34c), (void *) ((char *) self + 0x394), 4, 0x800, 0)) {
            func_ov133_0229ad68(self, 2);
        }
    }
    if (func_ov133_0229ad88(self, 4)) {
        if (func_020b9bbc((void *) ((char *) self + 0x370), (void *) ((char *) self + 0xb94), 6, 0x800, 0)) {
            func_ov133_0229ad68(self, 4);
        }
    }
}

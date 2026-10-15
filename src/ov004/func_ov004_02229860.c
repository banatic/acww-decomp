/* func_ov004_02229860 @ 0x02229860, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02229860 {
    int x, y, z;
};
struct VV {
    volatile int x, y, z;
};

extern int func_0201100c(void *self);

void func_ov004_02229860(char *self)
{
    struct VV old;
    struct UnkStruct_02229860 *p;
    int t, nx, nz, ox;

    p = (struct UnkStruct_02229860 *) (self + 0x5c);
    old.x = *(int *) (self + 0x5c);
    t = p->y;
    old.y = t;
    old.z = p->z;
    nz = *(int *) (self + 0x6fc);
    nx = *(int *) (self + 0x6f4);
    *(int *) (self + 0x5c) = nx;
    *(int *) (self + 0x60) = t;
    *(int *) (self + 0x64) = nz;
    *(int *) (self + 0x68) = *(int *) (self + 0x5c);
    *(int *) (self + 0x6c) = *(int *) (self + 0x60);
    *(int *) (self + 0x70) = *(int *) (self + 0x64);
    func_0201100c(self);
    ox = old.x;
    if (ox == *(int *) (self + 0x6f4)) {
        *(int *) (self + 0x64) = old.z;
    } else {
        *(int *) (self + 0x5c) = ox;
    }
}

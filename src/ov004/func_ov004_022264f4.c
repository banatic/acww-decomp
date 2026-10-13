/* func_ov004_022264f4 @ 0x022264f4, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022264f4 {
    int x;
    int y;
    int z;
};

extern void func_ov004_022265b0(void *a, int *x, int *z);
extern void func_ov004_022265dc(void *self, struct UnkStruct_022264f4 *p, int k, int arg);

void func_ov004_022264f4(char *self, int arg)
{
    struct UnkStruct_022264f4 p;

    func_ov004_022265b0(self + 0x8f0, &p.x, &p.z);
    if ((p.x & 0x80000) != 0) {
        p.x |= 0xfff00000;
    }
    if ((p.z & 0x80000) != 0) {
        p.z |= 0xfff00000;
    }
    func_ov004_022265dc(self, &p, 6, arg);
}

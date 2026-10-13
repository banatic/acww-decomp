/* func_ov004_02240740 @ 0x02240740, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern void func_ov004_022407e4(void *, int, int, int, int, int, int);
typedef struct {
    long x, y, z;
} UnkStruct_02240740;
void func_ov004_02240740(char *self)
{
    UnkStruct_02240740 *p;
    if (func_020644cc(0x64) > 0x32) {
        p = (UnkStruct_02240740 *) (self + 0x2c8);
        p->x = 0x16600;
        p->y = 0x1400;
        p->z = 0x14200;
    }
    func_ov004_022407e4(self, 0xc8, 0x28, 0x2d, 0x1e, 3, 0x19a);
}

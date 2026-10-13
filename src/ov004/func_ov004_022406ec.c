/* func_ov004_022406ec @ 0x022406ec, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern void func_ov004_022407e4(void *, int, int, int, int, int, int);
typedef struct {
    long x, y, z;
} UnkStruct_022406ec;
void func_ov004_022406ec(char *self)
{
    UnkStruct_022406ec *p;
    if (func_020644cc(0x64) > 0x32) {
        p = (UnkStruct_022406ec *) (self + 0x2c8);
        p->x = 0x12b00;
        p->y = 0x1a00;
        p->z = 0xda00;
    }
    func_ov004_022407e4(self, 0x64, 0x28, 0x32, 0x78, 0x1e, 0x266);
}

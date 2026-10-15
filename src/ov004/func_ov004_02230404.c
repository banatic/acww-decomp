/* func_ov004_02230404 @ 0x02230404, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

extern void func_ov004_0222c340(void *object);
extern void func_ov004_0222c3d4(void *object);
void func_ov004_02230404(char *self, int index)
{
    func_ov004_0222c3d4(self + 0x4b8 + 0xa4 * index);
    func_ov004_0222c340(self + 0x6a4 + (index << 2));
}

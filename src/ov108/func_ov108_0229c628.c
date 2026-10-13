/* func_ov108_0229c628 @ 0x0229c628, 0x4c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char c);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a374(void *p, int a);

void func_ov108_0229c628(unsigned char *obj)
{
    int result1;
    int result2;

    obj[0x2b5] = 0;
    result1 = func_ov002_02208ae4(obj + 0x24fc);
    result2 = func_ov002_02208ad8(obj + 0x24fc, obj[0x2b5]);
    func_ov002_0220a0b4(obj + 0x2498, result1, result2);
    func_ov002_0220a374(obj + 0x2498, 7);
}

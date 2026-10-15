/* func_ov105_0229c734 @ 0x0229c734, 0x24 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov105_0229c330(void *p, int a);
extern void func_ov002_02208090(void *p, int a);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);

void func_ov105_0229c734(void *p)
{
    func_ov002_02208090(p, 4);
    func_ov002_022080a0(p, 1);
    func_ov105_0229c330(p, 0x100);
}

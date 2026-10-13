/* func_ov111_022a0de8 @ 0x022a0de8, 0x20 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov111_0229ff88(void *p);
extern void func_ov002_02208090(void *p, int arg);
extern void func_ov002_022080a0(void *p, int arg);

int func_ov111_022a0de8(void *p)
{
    func_ov111_0229ff88(p);
    func_ov002_02208090(p, 0);
    func_ov002_022080a0(p, 1);
    return 1;
}

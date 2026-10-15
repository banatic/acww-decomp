/* func_ov096_022a1f84 @ 0x022a1f84, 0x20 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov096_022a1488(void *p);
extern void func_ov002_02208090(void *p, int x);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);

int func_ov096_022a1f84(void *p)
{
    func_ov096_022a1488(p);
    func_ov002_02208090(p, 0);
    func_ov002_022080a0((void *) (p), 1);
    return 1;
}

/* func_ov100_0229eacc @ 0x0229eacc, 0x20 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov100_0229e400(int);
extern void func_ov002_02208090(int, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);

int func_ov100_0229eacc(int p)
{
    func_ov100_0229e400(p);
    func_ov002_02208090(p, 0);
    func_ov002_022080a0((void *) (p), 0);
    return 1;
}

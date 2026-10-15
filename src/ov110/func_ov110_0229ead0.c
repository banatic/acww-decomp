/* func_ov110_0229ead0 @ 0x0229ead0, 0x20 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov110_0229e3c4(void *);
extern void func_ov002_02208090(void *, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);

int func_ov110_0229ead0(void *p)
{
    func_ov110_0229e3c4(p);
    func_ov002_02208090(p, 0);
    func_ov002_022080a0((void *) (p), 0);
    return 1;
}

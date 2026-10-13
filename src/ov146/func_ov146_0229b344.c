/* func_ov146_0229b344 @ 0x0229b344, 0x1e bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov146_0229acfc(void *);
extern void func_ov002_022080a0(void *);

int func_ov146_0229b344(void *self)
{
    func_ov146_0229acfc(self);
    ((unsigned char *) self)[0x8c] = 0;
    func_ov002_022080a0(self);
    return 1;
}

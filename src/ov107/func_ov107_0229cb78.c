/* func_ov107_0229cb78 @ 0x0229cb78, 0x2c bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov107_0229cce8(void *);
extern void func_ov002_022096d8(void *, int);
extern void func_ov002_02208098(void *, int);

void func_ov107_0229cb78(void *self)
{
    char *p;
    p = (char *) self + 0xbc;
    *p = 4;
    func_ov107_0229cce8(self);
    func_ov002_022096d8((char *) self + 0x2318, 0);
    func_ov002_02208098(self, 0xd);
}

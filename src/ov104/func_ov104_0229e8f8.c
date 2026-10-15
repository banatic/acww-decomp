/* func_ov104_0229e8f8 @ 0x0229e8f8, 0x2c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a098(void *receiver);
extern void func_ov002_0220af94(void *receiver);
extern int func_ov002_0220ab38(char *p, int n);

void func_ov104_0229e8f8(char *self)
{
    func_ov094_0229a098((void *) ((char *) self + 0xd80));
    func_ov002_0220af94((void *) ((char *) self + 0x41b4));
    func_ov002_0220ab38(self + 0x41b4, 0x65);
}

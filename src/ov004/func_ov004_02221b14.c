/* func_ov004_02221b14 @ 0x02221b14, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202e364(void *self);
extern void func_0201b38c(void *p, int a);
extern void func_0201b388(void *p, int a);
extern void func_0201b384(void *p, int a);
extern void func_0201c280(void *self, void *p);
extern void func_ov004_0222194c(void *p, void *self);

int func_ov004_02221b14(char *self)
{
    if (func_0202e364(self) == 0) {
        return 0;
    }
    func_0201b38c(self + 0x2a0, 0x1e);
    func_0201b388(self + 0x2a0, 0x1e);
    func_0201b384(self + 0x2a0, 0x1e);
    func_0201c280(self, self + 0x89c);
    func_ov004_0222194c(self + 0x89c, self);
    return 1;
}

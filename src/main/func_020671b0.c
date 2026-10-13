/* func_020671b0 @ 0x020671b0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ab4ec(void *ptr);
extern int func_020ab4e0(void *ptr);
extern void func_0206844c(void *self, int a, int b);
extern void func_02068428(void *self);
extern void func_020673e0(void *self);
extern void func_02067504(void *self);

void func_020671b0(void *self)
{
    int a;
    int b;
    a = func_020ab4ec((char *) self + 0x31c);
    b = func_020ab4e0((char *) self + 0x31c);
    func_0206844c(self, a, b);
    func_02068428(self);
    *((unsigned char *) self + 0x1e96) = 1;
    func_020673e0(self);
    func_02067504(self);
}

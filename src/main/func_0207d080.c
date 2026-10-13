/* func_0207d080 @ 0x0207d080, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138d6c(void *, int, int, void (*)(void), void (*)(void));
extern void func_02081710(void);
extern void func_020817a8(void);
extern void func_02079cc0(void *);
extern void func_0207a338(void *);
extern void func_0209a814(void *);

void *func_0207d080(void *self)
{
    func_02138d6c(self, 8, 0x7ec, func_020817a8, func_02081710);
    func_02079cc0((char *) self + 0x3f60);
    func_0207a338((char *) self + 0x3f7c);
    func_0209a814((char *) self + 0x3f90);
    *(unsigned int *) ((char *) self + 0x4050) = 0;
    *(unsigned int *) ((char *) self + 0x4054) = 0;
    *(unsigned int *) ((char *) self + 0x4058) = 0;
    *(unsigned int *) ((char *) self + 0x405c) = 0;
    return self;
}

/* func_020324fc @ 0x020324fc, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020da1b4;
extern void func_020012dc(void);
extern void func_020012e8(void);
extern void func_0202f2f0(void);
extern void func_02032550(void);
extern void func_020325b8(void *self);
extern void func_02138d6c(void *obj, int a, int b, void (*c)(void), void (*d)(void));

void *func_020324fc(void *self)
{
    *(void **) self = &data_020da1b4;
    func_02138d6c((char *) self + 0x30, 4, 0xc, func_020012e8, func_020012dc);
    func_02138d6c((char *) self + 0x60, 4, 8, func_02032550, func_0202f2f0);
    func_020325b8(self);
    return self;
}

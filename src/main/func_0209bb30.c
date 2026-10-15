/* func_0209bb30 @ 0x0209bb30, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209526c(void *addr);
extern void func_0209bd7c(void *addr);

void *func_0209bb30(void *addr)
{
    void *self = addr;
    func_0209526c((char *) self + 12);
    func_0209bd7c(self);
    return self;
}

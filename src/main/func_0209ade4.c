/* func_0209ade4 @ 0x0209ade4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209af2c(void *);
extern void func_0209bd7c(void *);
extern void func_02138c48(void *, int, int, void (*)(void));
extern void func_02003750(void);
extern void func_0209b594(void);

void *func_0209ade4(void *self)
{
    func_0209af2c((char *) self + 0xa4);
    func_0209bd7c((char *) self + 0x94);
    func_02138c48((char *) self + 0x60, 3, 0x10, func_02003750);
    func_02138c48(self, 2, 0x30, func_0209b594);
    return self;
}

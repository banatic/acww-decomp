/* func_02083b68 @ 0x02083b68, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083ca8(void *, int);
extern void func_02083bac(void);
extern void func_02083bd0(void);
extern void func_02138d6c(void *, int, int, void (*)(void), void (*)(void));
extern char data_020e1b54;

void *func_02083b68(void *self)
{
    void (*func)(void) = func_02083bac;
    func_02083ca8(self, 5);
    *(void **) self = &data_020e1b54;
    func_02138d6c((char *) self + 8, 5, 4, func_02083bd0, func);
    return self;
}

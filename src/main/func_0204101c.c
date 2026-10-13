/* func_0204101c @ 0x0204101c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020409c8(void *a, int b);
extern void func_020408d4(void *p);
extern void func_020ae3b8(void *p);
extern void func_020ae64c(void);
extern void func_020ae67c(void);
extern char data_021f3b30;

void func_0204101c(void *arg)
{
    char *p = func_020409c8(arg, 1);
    int i;
    void *lock;

    for (i = 0; i < 5; i++) {
        func_020408d4(p);
        p += 6;
    }
    lock = &data_021f3b30;
    func_020ae3b8(lock);
    func_020ae64c();
    func_020ae3b8(lock);
    func_020ae67c();
}

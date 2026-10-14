/* func_020902ac @ 0x020902ac, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void));
extern void func_020551e0(void *);
extern void func_020565b0(void);

void *func_020902ac(void *self)
{
    __cxa_vec_cleanup((void *) ((char *) self + 0xe8), 3, 0x20, func_020565b0);
    func_020551e0((void *) ((char *) self + 0x24));
    return self;
}
